/**
 * @file dbvh.h
 * @brief A dynamic bounding volume hierarchy is a spatial partitioning binary tree structure that supports frequent updates to the bounding volumes
 * of the objects it contains.
 * @author Tomás Marques
 * @date 26-09-2024
 */

#pragma once

#include <cstdint>

namespace cobalt {
    namespace core::geom {
        /**
         * @brief A dynamic bounding volume hierarchy is a spatial partitioning tree structure that supports frequent updates to the bounding volumes
         * of the objects it contains.
         * @tparam ElementType The type of the elements stored in the tree.
         */
        template <typename ElementType>
        class DBVH {
            static_assert(std::is_copy_constructible<ElementType>::value, "ElementType must be copy constructible.");
            class DBVHNode;

            public:
            DBVH() noexcept : root(-1) {}

            /**
             * @brief Inserts an element into the tree.
             * @param element The element to insert.
             * @return The index of the element in the tree.
             */
            int insert(const ElementType& element, const AABB& aabb) noexcept {
                int best = bestLeaf(root);
                int oldParent = nodes[best].parent;
                int newParent = reserveIndex();
                if (newParent == nodes.size()) {
                    nodes.emplace_back(oldParent);
                } else {
                    nodes.emplace(newParent, oldParent);
                }
                nodes[best].setParent(newParent);
                int newRight = reserveIndex();
                if (newRight == nodes.size()) {
                    nodes.emplace_back(newParent);
                } else {
                    nodes.emplace(newRight, newParent);
                }
                nodes[newRight].setAABB(aabb);
                nodes[newParent].setLeft(best);
                nodes[newParent].setRight(newRight);
                nodes[newParent].setAABB(aabb.combine(nodes[best].aabb));
                if (oldParent != -1) {
                    if (nodes[oldParent].left == best) {
                        nodes[oldParent].setLeft(newParent);
                    } else {
                        nodes[oldParent].setRight(newParent);
                    }
                } else {
                    root = newParent;
                }
                return newRight;
            }

            /**
             * @brief Removes an element from the tree.
             * @param index The index of the element to remove.
             */
            void remove(int index) noexcept {
                // Can't remove a non-existent node
                if (!isRealIndex(index)) {
                    return;
                }
                // Remove root node
                int parent = nodes[index].parent;
                if (parent == -1) {
                    root = -1;
                    return;
                }
                // Normal case
                int grandParent = nodes[parent].parent;
                int sibling = (nodes[parent].left == index) ? nodes[parent].right : nodes[parent].left;
                if (grandParent != -1) {
                    if (nodes[grandParent].left == parent) {
                        nodes[grandParent].setLeft(sibling);
                    } else {
                        nodes[grandParent].setRight(sibling);
                    }
                    nodes[sibling].setParent(grandParent);
                    fixBounds(grandParent);
                } else {
                    root = sibling;
                    nodes[sibling].setParent(-1);
                }
                releaseIndex(parent);
                releaseIndex(index);
            }

            /**
             * @brief Updates the bounding volume of an element in the tree.
             * @param index The index of the element to update.
             * @param aabb The new bounding volume of the element.
             */
            void update(int index, const AABB& aabb) noexcept {
                if (!isRealIndex(index)) {
                    return;
                }
                remove(index);
                insert(nodes[index].data, aabb);
                fixBounds(nodes[index].parent);
            }

            /**
             * @brief Queries the tree for elements that intersect a given range.
             * @param found The vector to store the found elements in.
             * @param range The range to query.
             */
            void query(std::vector<std::reference_wrapper<ElementType>>& found, const AABB& range) noexcept {
                if (root == -1) {
                    return;
                }
                std::stack<int> stack;
                stack.push(root);
                while (!stack.empty()) {
                    int index = stack.top();
                    stack.pop();
                    if (nodes[index].isLeaf()) {
                        if (range.intersects(nodes[index].aabb)) {
                            found.emplace_back(nodes[index].data);
                        }
                    } else {
                        if (range.intersects(nodes[nodes[index].left].aabb)) {
                            stack.push(nodes[index].left);
                        }
                        if (range.intersects(nodes[nodes[index].right].aabb)) {
                            stack.push(nodes[index].right);
                        }
                    }
                }
            }

            /**
             * @brief Queries the tree for elements that contain a given point.
             * @param found The vector to store the found elements in.
             * @param point The point to query.
             */
            void query(std::vector<std::reference_wrapper<ElementType>>& found, const glm::vec3& point) noexcept {
                if (root == -1) {
                    return;
                }
                std::stack<int> stack;
                stack.push(root);
                while (!stack.empty()) {
                    int index = stack.top();
                    stack.pop();
                    if (nodes[index].isLeaf()) {
                        if (nodes[index].aabb.contains(point)) {
                            found.emplace_back(nodes[index].data);
                        }
                    } else {
                        if (nodes[nodes[index].left].aabb.contains(point)) {
                            stack.push(nodes[index].left);
                        }
                        if (nodes[nodes[index].right].aabb.contains(point)) {
                            stack.push(nodes[index].right);
                        }
                    }
                }
            }

            /**
             * @brief Gets all the elements in the tree.
             * @param found The vector to store the elements in.
             */
            void query(std::vector<std::reference_wrapper<ElementType>>& found) noexcept {
                if (root == -1) {
                    return;
                }
                std::stack<int> stack;
                stack.push(root);
                while (!stack.empty()) {
                    int index = stack.top();
                    stack.pop();
                    if (nodes[index].isLeaf()) {
                        found.emplace_back(nodes[index].data);
                    } else {
                        stack.push(nodes[index].left);
                        stack.push(nodes[index].right);
                    }
                }
            }

            private:
            int root;                      ///< The index of the root node.
            std::vector<DBVHNode> nodes;   ///< The nodes in the tree.
            std::vector<int> freeIndices;  ///< Unused indices in the tree.

            /**
             * @brief A node in the dynamic bounding volume hierarchy.
             */
            class DBVHNode {
                friend class DBVH;

                public:
                /**
                 * @brief Constructs a new node with the given parent.
                 * @param parent The index of the parent. If the node is the root, the parent is -1.
                 */
                DBVHNode(int parent) noexcept : left(0), right(0), parent(parent) {}

                /**
                 * @brief Checks if the node is a leaf.
                 * @return True if the node is a leaf, false otherwise.
                 */
                bool isLeaf() const noexcept { return left == -1 && right == -1; }

                /**
                 * @brief Gets the data stored in the node.
                 * @return The data stored in the node.
                 */
                void setAABB(const AABB& aabb) noexcept { this->aabb = aabb; }

                /**
                 * @brief Sets the left child of the node.
                 * @param left The index of the left child.
                 */
                void setLeft(int left) noexcept { this->left = left; }

                /**
                 * @brief Sets the right child of the node.
                 * @param right The index of the right child.
                 */
                void setRight(int right) noexcept { this->right = right; }

                /**
                 * @brief Sets the parent of the node.
                 * @param parent The index of the parent.
                 */
                void setParent(int parent) noexcept { this->parent = parent; }

                private:
                ElementType data;  ///< The data stored in the node.
                AABB bounds;       ///< The bounding volume of the node.
                int left;          ///< The index of the left child.
                int right;         ///< The index of the right child.
                int parent;        ///< The index of the parent.
            };

            /**
             * @brief Fixes the bounds of the tree after an update to a bounding volume.
             * @param index The index to start at.
             */
            void fixBounds(int index) {
                while (index != -1) {
                    // TODO: Balance the tree
                    nodes[index].setAABB(nodes[nodes[index].left].aabb.combine(nodes[nodes[index].right].aabb));
                    index = nodes[index].parent;
                }
            }

            /**
             * @brief Finds the best leaf to convert to a branch.
             * @param start The index to start at.
             * @return The index of the best leaf to convert to a branch.
             */
            int bestLeaf(int start) {
                int index = start;
                while (!nodes[index].isLeaf()) {
                    int left = nodes[index].left;
                    int right = nodes[index].right;

                    float areaLeft = nodes[left].aabb.combine(nodes[index].aabb).area();
                    float areaRight = nodes[right].aabb.combine(nodes[index].aabb).area();

                    index = (areaLeft < areaRight) ? left : right;
                }
                return index;
            }

            /**
             * @brief Gets a free index for a new node.
             * @return The index for a new node.
             */
            int reserveIndex() {
                if (freeIndices.empty()) {
                    return nodes.size();
                }
                int index = freeIndices.front();
                freeIndices.erase(freeIndices.begin());
                return index;
            }

            /**
             * @brief Releases an index for reuse.
             * @param index The index to release.
             */
            void releaseIndex(int index) {
                if (!isRealIndex(index)) {
                    return;
                }
                freeIndices.push_back(index);
            }

            /**
             * @brief Checks if there is an active node at the given index.
             * @param index The index to check.
             * @return True if there is an active node at the given index, false otherwise.
             */
            bool isRealIndex(int index) const noexcept {
                if (std::find(freeIndices.begin(), freeIndices.end(), index) == freeIndices.end()) {
                    return index >= 0 && index < nodes.size();
                }
                return false;
            }
        };
    }  // namespace core::geom
}  // namespace cobalt