/**
 * @file bvh.h
 * @brief A bounding volume hierarchy is a tree structure on a set of geometric objects, most commonly used for collision detection and ray tracing.
 * acceleration.
 * @author Tomás Marques
 * @date 02-09-2024
 */

#pragma once

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
            BVH(const uint maxLeafSize) noexcept : maxLeafSize(maxLeafSize) {}

            private:
            /**
             * @brief A node in the BVH tree. Can be either an internal node or a leaf node.
             */
            class BVHNode {
                public:
                /**
                 * @brief Checks if the node is a leaf node.
                 * @return
                 */
                bool isLeaf() const noexcept { return !left && !right; }

                /**
                 * @brief Builds the BVH sub-tree from a set of elements, using a given split strategy.
                 * @param elements The set of elements to build the BVH from.
                 * @param splitStrategy The strategy to use for splitting the elements.
                 * @see SplitStrategy
                 */
                void build(Vector<ElementType*> elements, const SplitStrategy<ElementType>& splitStrategy) {
                    // Leaf node
                    if (elements.size() <= maxLeafSize) {
                        this->elements = Move(elements);
                        AABB totalBounds;
                        for (ElementType* element : this->elements) {
                            totalBounds += element->getBounds();
                        }
                        bounds = totalBounds;
                        bounds.step();  // Expand the bounds slightly to avoid floating point errors.
                        return;
                    }

                    // Internal node
                    Pair<Vector<ElementType*>, Vector<ElementType*>> split = splitStrategy.split(elements);
                    left = CreateScope<BVHNode>();
                    left->build(Move(split.first), splitStrategy);
                    right = CreateScope<BVHNode>();
                    right->build(Move(split.second), splitStrategy);
                    bounds = left->bounds + right->bounds;
                }

                private:
                AABB bounds;                    ///< The bounding volume of the node. Encompasses all the elements in the node's subtree.
                Scope<BVHNode> left;            ///< The left child node.
                Scope<BVHNode> right;           ///< The right child node.
                Vector<ElementType*> elements;  ///< The elements in the node. Only present in leaf nodes.
            };

            const uint maxLeafSize;
        };
    }  // namespace core::geom
}  // namespace cobalt