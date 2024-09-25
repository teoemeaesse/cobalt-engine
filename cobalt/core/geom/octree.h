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
         * @tparam ElementType The type of the data stored in the Octree.
         */
        template <typename ElementType>
        class Octree {
            public:
            /**
             * @brief A configuration for the Octree parameters.
             */
            struct Configuration {
                const uint maxDepth;                              // The maximum depth of the octree. 0 means no depth limit.
                const uint maxElements;                           // The maximum number of elements in a node. This must be at least 1.
                Func<AABB(const ElementType&)> getElementBounds;  // The function to get an element's bounding box.

                /**
                 * @brief Creates an Octree configuration.
                 * @param getElementBounds The function to get an element's bounding box.
                 * @param maxDepth The maximum depth of the Octree. 0 means no depth limit.
                 * @param maxElements The maximum number of elements in a node. This must be at least 1.
                 */
                Configuration(Func<AABB(const ElementType&)> getElementBounds, const uint maxDepth = 0, const uint maxElements = 8) noexcept
                    : getElementBounds(getElementBounds), maxDepth(maxDepth), maxElements(maxElements) {}
            };

            /**
             * @brief Creates an octree.
             * @param bounds The maximum bounds of the octree.
             * @param config The configuration of the octree.
             * @see Configuration
             */
            Octree(const AABB& bounds, const Configuration& config) noexcept : root(bounds, config) {}
            /**
             * @brief Destroys the octree.
             */
            ~Octree() noexcept = default;

            /**
             * @brief Queries the octree for elements that intersect a given range. If a range is not provided, the function returns all elements in
             * the octree.
             * @param found The vector to store the found elements in.
             * @param range The range to query. If not provided, the function returns all elements in the octree.
             */
            void query(Vec<Wrap<ElementType>>& found, Opt<AABB> range = None) { root.query(found, range); }
            /**
             * @brief Queries the octree for elements that intersect a given point. If a point is not provided, the function returns all elements in
             * the octree.
             * @param found The vector to store the found elements in.
             * @param point The point to query. If not provided, the function returns all elements in the octree.
             */
            void query(Vec<Wrap<ElementType>>& found, const glm::vec3& point) { root.query(found, point); }

            /**
             * @brief Copy-inserts an element into the tree. The bounds for this element MUST NOT BE VOID.
             * @param element The element to insert. Must be copy-constructible.
             */
            void insert(const ElementType& element) { root.insert(element); }

            class Debug;

            private:
            /**
             * @brief A node in the octree. The root node is the starting point of the octree, and all other nodes are its children.
             */
            class OctreeNode {
                friend class Octree<ElementType>::Debug;

                public:
                /**
                 * @brief Creates an octree node.
                 * @param bounds The bounds of the node.
                 * @param config The configuration of the octree.
                 * @param depth The depth of the node.
                 */
                OctreeNode(const AABB& bounds, const Configuration& config, const uint depth = 0) noexcept
                    : bounds(bounds), config(config), depth(depth) {}
                ~OctreeNode() noexcept = default;
                OctreeNode(const OctreeNode&) = delete;
                OctreeNode& operator=(const OctreeNode&) = delete;
                OctreeNode(OctreeNode&&) = default;
                OctreeNode& operator=(OctreeNode&&) = default;

                /**
                 * @brief Queries the octree for elements that intersect a given range. If a range is not provided, the function returns all elements
                 * in the octree.
                 * @param found The vector to store the found elements in.
                 * @param range The range to query. If not provided, the function returns all elements in the octree.
                 */
                void query(Vec<Wrap<ElementType>>& found, Opt<AABB> range = None) {
                    if (range.has_value() && !range.value().intersects(bounds)) {
                        return;
                    }
                    for (auto& element : data) {
                        const AABB& elementBounds = config.getElementBounds(element);
                        if (!range.has_value() || range.value().contains(elementBounds)) {
                            found.push_back(element);
                        }
                    }
                    if (!isLeaf()) {
                        for (auto& child : children) {
                            child.query(found, range);
                        }
                    }
                }
                /**
                 * @brief Queries the octree for elements that intersect a given point. If a point is not provided, the function returns all elements
                 * in the octree.
                 * @param found The vector to store the found elements in.
                 * @param point The point to query. If not provided, the function returns all elements in the octree.
                 */
                void query(Vec<Wrap<ElementType>>& found, const glm::vec3& point) {
                    if (!bounds.contains(point)) {
                        return;
                    }
                    for (auto& element : data) {
                        const AABB& elementBounds = config.getElementBounds(element);
                        if (elementBounds.contains(point)) {
                            found.push_back(element);
                        }
                    }
                    if (!isLeaf()) {
                        for (auto& child : children) {
                            child.query(found, point);
                        }
                    }
                }

                /**
                 * @brief Copy-inserts an element into the tree. The bounds for this element MUST NOT BE VOID.
                 * @param element The element to insert. Must be copy-constructible.
                 */
                void insert(ConstWrap<ElementType> element) {
                    static_assert(std::is_copy_constructible<ElementType>::value, "ElementType must be copy constructible.");
                    const AABB& elementBounds = config.getElementBounds(element);
                    if (!this->bounds.intersects(elementBounds)) return;
                    if (isLeaf()) {
                        data.push_back(CreateWrap<ElementType>(element));
                        if (data.size() > config.maxElements && (config.maxDepth == 0 || depth < config.maxDepth)) {
                            split();
                        }
                        return;
                    }
                    for (auto& child : children) {
                        if (child.bounds.contains(elementBounds)) {
                            child.insert(CreateWrap<ElementType>(element));
                            return;
                        }
                    }
                    data.push_back(element);
                }

                /**
                 * @brief Checks if the node is a leaf in the octree.
                 * @return Whether the node is a leaf.
                 */
                bool isLeaf() const noexcept { return children.empty(); }

                private:
                Vec<OctreeNode> children;     // The children of the node.
                Vec<ElementType> data;        // The data stored in the node.
                AABB bounds;                  // The bounds of the node.
                const uint depth;             // The depth of the node.
                const Configuration& config;  // The configuration of the octree.

                /**
                 * @brief Splits the node into 8 children and recursively distribute the data.
                 */
                void split() {
                    glm::vec3 min = bounds.getMin();
                    glm::vec3 max = bounds.getMax();
                    glm::vec3 mid = {(min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2};

                    children.emplace_back((AABB){{min.x, min.y, min.z}, {mid.x, mid.y, mid.z}}, config, depth + 1);
                    children.emplace_back((AABB){{min.x, min.y, mid.z}, {mid.x, mid.y, max.z}}, config, depth + 1);
                    children.emplace_back((AABB){{min.x, mid.y, min.z}, {mid.x, max.y, mid.z}}, config, depth + 1);
                    children.emplace_back((AABB){{min.x, mid.y, mid.z}, {mid.x, max.y, max.z}}, config, depth + 1);
                    children.emplace_back((AABB){{mid.x, min.y, min.z}, {max.x, mid.y, mid.z}}, config, depth + 1);
                    children.emplace_back((AABB){{mid.x, min.y, mid.z}, {max.x, mid.y, max.z}}, config, depth + 1);
                    children.emplace_back((AABB){{mid.x, mid.y, min.z}, {max.x, max.y, mid.z}}, config, depth + 1);
                    children.emplace_back((AABB){{mid.x, mid.y, mid.z}, {max.x, max.y, max.z}}, config, depth + 1);
                    Vec<ElementType> tempData = Move(data);
                    data.clear();

                    for (const auto& element : tempData) {
                        const AABB& elementBounds = config.getElementBounds(element);
                        bool inserted = false;
                        for (auto& child : children) {
                            if (child.bounds.contains(elementBounds)) {
                                child.insert(CreateWrap<ElementType>(element));
                                inserted = true;
                                break;
                            }
                        }
                        if (!inserted) {
                            data.push_back(element);
                        }
                    }
                }
            };

            OctreeNode root;  ///< The root node of the octree.s

#ifdef TEST_ENVIRONMENT
            public:
            /**
             * @brief A dummy class for debugging the octree. Never use this in production code.
             * @tparam ElementType The type of the data stored in the Octree.
             * @warning This is to be used for testing, never in production code.
             */
            class Debug {
                public:
                /**
                 * @brief Gets the root node of the octree.
                 * @param octree The octree.
                 * @return The root node.
                 */
                static const OctreeNode& getRoot(Octree<ElementType>& octree) { return octree.root; }

                /**
                 * @brief Gets the data of a node.
                 * @param node The node.
                 * @return The data.
                 */
                static const Vec<ElementType>& getData(const OctreeNode& node) { return node.data; }

                /**
                 * @brief Gets the children of a node.
                 * @param node The node.
                 * @return The children.
                 */
                static const Vec<OctreeNode>& getChildren(const OctreeNode& node) { return node.children; }

                /**
                 * @brief Gets the bounds of a node.
                 * @param node The node.
                 * @return The bounds.
                 */
                static const AABB& getBounds(const OctreeNode& node) { return node.bounds; }
            };
#endif
        };  // namespace core::geom
    }  // namespace core::geom
}  // namespace cobalt