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
         * @brief A node in an octree. This class should be extended.
         *
         * @tparam T The type of the data stored in the octree.
         */
        template <typename T>
        class OctreeNode {
            public:
            /**
             * @brief Create an octree node.
             * @param bounds The bounds of the node.
             * @param getElementBounds The function to get an element's bounding box.
             */
            OctreeNode(const AABB3& bounds, Func<AABB3(const T&)> getElementBounds) noexcept : bounds(bounds), getElementBounds(getElementBounds) {}

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
                const AABB3& bounds = getElementBounds(element);
                if (!this->bounds.intersects(bounds)) return;
                if (isLeaf()) {
                    data.push_back(element);
                    if (shouldSplit()) {
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

            /**
             * @brief Check if this node should subdivide any further.
             * @return Whether the node should subdivide.
             */
            virtual bool shouldSplit() const = 0;

            private:
            Vec<OctreeNode<T>> children;  // The children of the node.
            Vec<T> data;                  // The data stored in the node.
            AABB3 bounds;                 // The bounds of the node.

            Func<AABB3(const T&)> getElementBounds;  // The function to get an element's bounding box.

            /**
             * @brief Split the node into 8 children and recursively distribute the data.
             */
            void split() {
                glm::vec3 min = bounds.getMin();
                glm::vec3 max = bounds.getMax();
                glm::vec3 mid = {(min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2};

                children.emplace_back({min.x, min.y, min.z}, {mid.x, mid.y, mid.z});
                children.emplace_back({min.x, min.y, mid.z}, {mid.x, mid.y, max.z});
                children.emplace_back({min.x, mid.y, min.z}, {mid.x, max.y, mid.z});
                children.emplace_back({min.x, mid.y, mid.z}, {mid.x, max.y, max.z});
                children.emplace_back({mid.x, min.y, min.z}, {max.x, mid.y, mid.z});
                children.emplace_back({mid.x, min.y, mid.z}, {max.x, mid.y, max.z});
                children.emplace_back({mid.x, mid.y, min.z}, {max.x, max.y, mid.z});
                children.emplace_back({mid.x, mid.y, mid.z}, {max.x, max.y, max.z});

                for (const auto& element : data) {
                    for (auto& child : children) {
                        child->insert(element);
                    }
                }
                data.clear();
            }
        };
    }  // namespace core::geom
}  // namespace cobalt