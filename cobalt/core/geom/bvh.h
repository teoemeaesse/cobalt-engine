/**
 * @file bvh.h
 * @brief A bounding volume hierarchy is a tree structure on a set of geometric objects, most commonly used for collision detection and ray tracing.
 * acceleration.
 * @author Tomás Marques
 * @date 02-09-2024
 */

#pragma once

#include "core/geom/strategy/split_strategy.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::geom {
        /**
         * @brief A bounding volume hierarchy is a tree structure on a set of geometric objects, most commonly used for collision detection and ray
         * tracing. Being a tree, it has a root node, internal nodes and leaf nodes. The root node contains the entire set of objects, and each
         * internal node contains a bounding volume that encompasses all the objects in its child nodes.
         * @tparam ElementType The type of the data stored in the BVH. Must have a bounding volume (even if null).
         */
        template <typename ElementType>
        class BVH {
            public:
            /**
             * @brief A configuration for the BVH parameters.
             */
            struct Configuration {
                const uint maxDepth;                              ///< The maximum depth of the BVH. 0 means no depth limit.
                const uint maxElements;                           ///< The maximum number of elements in a leaf node.
                Scope<SplitStrategy<ElementType>> splitStrategy;  ///< The strategy to use for spatially splitting the elements.

                /**
                 * @brief Creates a BVH configuration.
                 * @param splitStrategy The strategy to use for spatially splitting the elements.
                 * @param maxElements The maximum number of elements in a leaf node.
                 * @param maxDepth The maximum depth of the BVH. 0 means no depth limit.
                 */
                Configuration(Scope<SplitStrategy<ElementType>>&& splitStrategy, const uint maxElements = 8, const uint maxDepth = 0) noexcept
                    : splitStrategy(Move(splitStrategy)), maxElements(maxElements), maxDepth(maxDepth) {}

                Configuration(const Configuration&) = delete;
                Configuration& operator=(const Configuration&) = delete;
            };

            /**
             * @brief Creates a BVH from a set of elements and a configuration.
             * @param data The set of elements to build the BVH from.
             * @param config The configuration of the BVH.
             */
            BVH(const Vec<ElementType>& data, const Configuration& config) noexcept : root(data, config) {}

            /**
             * @brief Queries the BVH for elements that intersect a given range.
             * @param found The vector to store the found elements in.
             * @param range The range to query.
             */
            void query(Vec<Wrap<ElementType>>& found, const AABB& range) noexcept { root.query(found, range); }
            /**
             * @brief Queries the BVH for elements that contain a given point.
             * @param found The vector to store the found elements in.
             * @param point The point to query.
             */
            void query(Vec<Wrap<ElementType>>& found, const glm::vec3& point) noexcept { root.query(found, point); }
            /**
             * @brief Queries the BVH for all elements.
             * @param found The vector to store the found elements in.
             */
            void query(Vec<Wrap<ElementType>>& found) noexcept { root.query(found); }

            class Debug;

            private:
            /**
             * @brief A node in the BVH tree. Can be either an internal node or a leaf node.
             */
            class BVHNode {
                friend class BVH<ElementType>::Debug;

                public:
                /**
                 * @brief Creates a BVH node from a set of elements and a configuration.
                 * @param data The set of elements to build the BVH from.
                 * @param config The configuration of the BVH.
                 */
                BVHNode(const Vec<ElementType>& data, const Configuration& config, const uint depth = 0) : config(config), depth(depth) {
                    if (!data.empty()) build(data);
                }

                /**
                 * @brief Checks if the node is a leaf node.
                 * @return True if the node is a leaf node, false otherwise.
                 */
                bool isLeaf() const noexcept { return !left && !right; }

                /**
                 * @brief Builds the BVH sub-tree from a set of elements, using a given split strategy.
                 * @param data The set of elements to build the BVH from.
                 * @param splitStrategy The strategy to use for splitting the elements.
                 * @see SplitStrategy
                 */
                void build(const Vec<ElementType>& data) {
                    // Leaf node
                    if (data.size() <= config.maxElements || data.size() <= 1 || (config.maxDepth > 0 && depth >= config.maxDepth)) {
                        AABB totalBounds;
                        for (auto& element : data) {
                            totalBounds += config.splitStrategy->getElementBounds(element);
                            this->data.push_back(element);
                        }
                        bounds = totalBounds;
                        bounds.step();  // Expand the bounds slightly to avoid floating point errors.
                        return;
                    }

                    // Internal node
                    Pair<Vec<ElementType>, Vec<ElementType>> split = config.splitStrategy->split(data);

                    if (split.first.empty() || split.second.empty()) {
                        AABB totalBounds;
                        for (auto& element : data) {
                            totalBounds += config.splitStrategy->getElementBounds(element);
                            this->data.push_back(element);
                        }
                        bounds = totalBounds;
                        bounds.step();  // Expand the bounds slightly to avoid floating point errors.
                        return;
                    }

                    left = CreateScope<BVHNode>(split.first, config, depth + 1);
                    right = CreateScope<BVHNode>(split.second, config, depth + 1);
                    bounds = left->bounds + right->bounds;
                }

                /**
                 * @brief Queries the BVH for elements that intersect a given range.
                 * @param found The vector to store the found elements in.
                 * @param range The range to query.
                 */
                void query(Vec<Wrap<ElementType>>& found, const AABB& range) {
                    if (!bounds.intersects(range)) return;

                    if (isLeaf()) {
                        for (auto& element : data) {
                            if (range.intersects(config.splitStrategy->getElementBounds(element))) {
                                found.push_back(CreateWrap<ElementType>(element));
                            }
                        }
                    } else {
                        left->query(found, range);
                        right->query(found, range);
                    }
                }
                /**
                 * @brief Queries the BVH for elements that contain a given point.
                 * @param found The vector to store the found elements in.
                 * @param point The point to query.
                 */
                void query(Vec<Wrap<ElementType>>& found, const glm::vec3& point) {
                    if (!bounds.contains(point)) return;

                    if (isLeaf()) {
                        for (auto& element : data) {
                            if (config.splitStrategy->getElementBounds(element).contains(point)) {
                                found.push_back(CreateWrap<ElementType>(element));
                            }
                        }
                    } else {
                        left->query(found, point);
                        right->query(found, point);
                    }
                }
                /**
                 * @brief Queries the BVH for all elements.
                 * @param found The vector to store the found elements in.
                 */
                void query(Vec<Wrap<ElementType>>& found) {
                    if (isLeaf()) {
                        for (auto& element : data) {
                            found.push_back(CreateWrap<ElementType>(element));
                        }
                    } else {
                        left->query(found);
                        right->query(found);
                    }
                }

                private:
                AABB bounds;                  ///< The bounding volume of the node. Encompasses all the elements in the node's subtree.
                Scope<BVHNode> left;          ///< The left child node.
                Scope<BVHNode> right;         ///< The right child node.
                Vec<ElementType> data;        ///< The elements in the node. Only present in leaf nodes.
                const Configuration& config;  ///< The configuration of the BVH.
                const uint depth;             ///< The depth of the node in the BVH.
            };

            BVHNode root;  ///< The root node of the BVH.

#ifdef TEST_ENVIRONMENT
            public:
            /**
             * @brief A dummy class for debugging the BVH. Never use this in production code.
             * @tparam ElementType The type of the data stored in the BVH.
             * @warning This is to be used for testing, never in production code.
             */
            class Debug {
                public:
                /**
                 * @brief Gets the root node of the BVH.
                 * @param bvh The BVH.
                 * @return The root node.
                 */
                static const BVHNode& getRoot(const BVH<ElementType>& bvh) { return bvh.root; }

                /**
                 * @brief Gets the left child of a BVH node.
                 * @param node The node.
                 * @return The left child.
                 */
                static const BVHNode& getLeft(const BVHNode& node) { return *node.left; }

                /**
                 * @brief Gets the right child of a BVH node.
                 * @param node The node.
                 * @return The right child.
                 */
                static const BVHNode& getRight(const BVHNode& node) { return *node.right; }

                /**
                 * @brief Gets the elements in a BVH node.
                 * @param node The node.
                 * @return The elements.
                 */
                static const Vec<ElementType>& getData(const BVHNode& node) { return node.data; }

                /**
                 * @brief Gets the bounding volume of a BVH node.
                 * @param node The node.
                 * @return The bounding volume.
                 */
                static const AABB& getBounds(const BVHNode& node) { return node.bounds; }

                /**
                 * @brief Checks if a BVH node is a leaf node.
                 * @param node The node.
                 * @return True if the node is a leaf node, false otherwise.
                 */
                static bool isLeaf(const BVHNode& node) { return node.isLeaf(); }
            };
#endif
        };
    }  // namespace core::geom
}  // namespace cobalt