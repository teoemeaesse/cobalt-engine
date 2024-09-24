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
                const uint maxDepth;                                    ///< The maximum depth of the BVH. 0 means no depth limit.
                const uint maxElements;                                 ///< The maximum number of elements in a leaf node.
                Scope<const SplitStrategy<ElementType>> splitStrategy;  ///< The strategy to use for spatially splitting the elements.

                /**
                 * @brief Creates a BVH configuration.
                 * @param splitStrategy The strategy to use for spatially splitting the elements.
                 * @param maxElements The maximum number of elements in a leaf node.
                 * @param maxDepth The maximum depth of the BVH. 0 means no depth limit.
                 */
                Configuration(Scope<const SplitStrategy<ElementType>>&& splitStrategy, const uint maxElements = 8, const uint maxDepth = 0) noexcept
                    : splitStrategy(Move(splitStrategy)), maxElements(maxElements), maxDepth(maxDepth) {}
            };

            /**
             * @brief Creates a BVH from a set of elements and a configuration.
             * @param data The set of elements to build the BVH from.
             * @param config The configuration of the BVH.
             */
            BVH(const Vec<ElementType>& data, const Configuration& config) noexcept : root(config) { root.build(data); }

            class Debug;

            private:
            /**
             * @brief A node in the BVH tree. Can be either an internal node or a leaf node.
             */
            class BVHNode {
                friend class BVH<ElementType>::Debug;

                public:
                BVHNode(const Configuration& config) : config(config) {}
                /**
                 * @brief Checks if the node is a leaf node.
                 * @return
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
                    if (data.size() <= config.maxElements) {
                        AABB totalBounds;
                        for (auto& element : data) {
                            totalBounds += element->getBounds();
                            this->data.push_back(element);
                        }
                        bounds = totalBounds;
                        bounds.step();  // Expand the bounds slightly to avoid floating point errors.
                        return;
                    }

                    // Internal node
                    Pair<Vec<ElementType>, Vec<ElementType>> split = config.splitStrategy->split(this->data);
                    left = CreateScope<BVHNode>(split.first, config);
                    right = CreateScope<BVHNode>(split.first, config);
                    bounds = left.bounds + right.bounds;
                }

                /**
                 * @brief Queries the BVH for elements that intersect a given range. If a range is not provided, the function returns all elements in
                 * the BVH.
                 * @param found The vector to store the found elements in.
                 * @param range The range to query. If not provided, the function returns all elements in the BVH.
                 */
                void query(Vec<Wrap<ElementType>>& found, Opt<ConstWrap<AABB>> range = None) const {
                    if (range.has_value() && !bounds.intersects(range.value())) return;

                    if (isLeaf()) {
                        for (auto& element : data) {
                            if (range.value().get().intersects(config.splitStrategy->getElementBounds(element))) {
                                found.push_back(element);
                            }
                        }
                    } else {
                        left->query(range, found);
                        right->query(range, found);
                    }
                }
                /**
                 * @brief Queries the BVH for elements that contain a given point. If a point is not provided, the function returns all elements in
                 * the BVH.
                 * @param found The vector to store the found elements in.
                 * @param point The point to query. If not provided, the function returns all elements in the BVH.
                 */
                void query(Vec<Wrap<ElementType>>& found, Opt<ConstWrap<glm::vec3>> point = None) const {
                    if (point.has_value() && !bounds.contains(point.value())) return;

                    if (isLeaf()) {
                        for (auto& element : data) {
                            if (config.splitStrategy->getElementBounds(element).contains(point)) {
                                found.push_back(element);
                            }
                        }
                    } else {
                        left->query(point, found);
                        right->query(point, found);
                    }
                }

                private:
                AABB bounds;                  ///< The bounding volume of the node. Encompasses all the elements in the node's subtree.
                Scope<BVHNode> left;          ///< The left child node.
                Scope<BVHNode> right;         ///< The right child node.
                Vec<ElementType> data;        ///< The elements in the node. Only present in leaf nodes.
                const Configuration& config;  ///< The configuration of the BVH.
            };

            BVHNode root;  ///< The root node of the BVH.

            public:
            /**
             * @brief A dummy class for debugging the BVH. Never use this in production code.
             * @tparam ElementType The type of the data stored in the BVH.
             * @warning This is to be used for testing, never in production code.
             */
            class Debug {
                /**
                 * @brief Gets the root node of the BVH.
                 * @param bvh The BVH.
                 * @return The root node.
                 */
                static const BVHNode& getRoot(const BVH<ElementType>& bvh) { return bvh.root; }
            };
        };
    }  // namespace core::geom
}  // namespace cobalt