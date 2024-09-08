/**
 * @file octree.h
 * @brief An octree data structure for spatial partitioning.
 * @author Tomás Marques
 * @date 23-08-2024
 */

#pragma once

#include "core/geom/aabb.h"

namespace cobalt {
    namespace core::geom {
        /**
         * @brief An Octree divides 3D space into 8 octants, each of which can be further divided into 8 octants, and so on. Useful for collision
         * detection and spatial partitioning in general.
         * @tparam T The type of the data stored in the Octree.
         */
        template <typename T>
        class Octree {
            public:
            /**
             * @brief A configuration for the octree parameters.
             */
            struct Configuration {
                const uint maxDepth;                    // The maximum depth of the octree. 0 means no depth limit.
                const uint maxElements;                 // The maximum number of elements in a node. This must be at least 1.
                Func<AABB(const T&)> getElementBounds;  // The function to get an element's bounding box.

                /**
                 * @brief Create an octree configuration.
                 * @param getElementBounds The function to get an element's bounding box.
                 * @param maxDepth The maximum depth of the octree. 0 means no depth limit.
                 * @param maxElements The maximum number of elements in a node. This must be at least 1.
                 * @see Octree
                 * @see OctreeNode
                 */
                Configuration(Func<AABB(const T&)> getElementBounds, const uint maxDepth = 0, const uint maxElements = 8) noexcept
                    : getElementBounds(getElementBounds), maxDepth(maxDepth), maxElements(maxElements) {}
            };

            /**
             * @brief Create an octree.
             * @param bounds The maximum bounds of the octree.
             * @param config The configuration of the octree.
             * @see Configuration
             */
            Octree(const AABB& bounds, const Configuration& config) noexcept : root(bounds, config) {}

            private:
            class OctreeNode {
                public:
                /**
                 * @brief Create an octree node.
                 * @param bounds The bounds of the node.
                 * @param config The configuration of the octree.
                 * @param depth The depth of the node.
                 */
                OctreeNode(const AABB& bounds, const Configuration& config, const uint depth = 0) noexcept : bounds(bounds), depth(depth) {}

                ~OctreeNode() noexcept = default;

                OctreeNode(const OctreeNode&) = delete;

                OctreeNode& operator=(const OctreeNode&) = delete;

                OctreeNode(OctreeNode&&) = delete;

                OctreeNode& operator=(OctreeNode&&) = delete;

                /**
                 * @brief Copy an element into the tree.
                 * @param element The element to copy. Must be copy-constructible.
                 */
                void insert(const T& element) {
                    static_assert(std::is_copy_constructible<T>::value, "T must be copy constructible.");
                    const AABB& bounds = config.getElementBounds(element);
                    if (!this->bounds.intersects(bounds)) return;
                    if (isLeaf()) {
                        data.push_back(element);
                        if (data.size() > config.maxElements && (config.maxDepth == 0 || depth < config.maxDepth)) {
                            split();
                        }
                        return;
                    }
                    for (auto& child : children) {
                        child->insert(element);
                    }
                }

                /**
                 * @brief Check if the node is a leaf in the octree.
                 * @return Whether the node is a leaf.
                 */
                bool isLeaf() const noexcept { return children.empty(); }

                private:
                Vec<OctreeNode> children;     // The children of the node.
                Vec<T> data;                  // The data stored in the node.
                AABB bounds;                  // The bounds of the node.
                const uint depth;             // The depth of the node.
                const Configuration& config;  // The configuration of the octree.

                /**
                 * @brief Split the node into 8 children and recursively distribute the data.
                 */
                void split() {
                    glm::vec3 min = bounds.getMin();
                    glm::vec3 max = bounds.getMax();
                    glm::vec3 mid = {(min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2};

                    children.emplace_back({{min.x, min.y, min.z}, {mid.x, mid.y, mid.z}}, depth + 1);
                    children.emplace_back({{min.x, min.y, mid.z}, {mid.x, mid.y, max.z}}, depth + 1);
                    children.emplace_back({{min.x, mid.y, min.z}, {mid.x, max.y, mid.z}}, depth + 1);
                    children.emplace_back({{min.x, mid.y, mid.z}, {mid.x, max.y, max.z}}, depth + 1);
                    children.emplace_back({{mid.x, min.y, min.z}, {max.x, mid.y, mid.z}}, depth + 1);
                    children.emplace_back({{mid.x, min.y, mid.z}, {max.x, mid.y, max.z}}, depth + 1);
                    children.emplace_back({{mid.x, mid.y, min.z}, {max.x, max.y, mid.z}}, depth + 1);
                    children.emplace_back({{mid.x, mid.y, mid.z}, {max.x, max.y, max.z}}, depth + 1);

                    for (const auto& element : data) {
                        for (auto& child : children) {
                            child->insert(element);
                        }
                    }
                    data.clear();
                }
            };

            OctreeNode root;  // The root node of the octree.s
        };  // namespace core::geom
    }  // namespace core::geom
}  // namespace cobalt