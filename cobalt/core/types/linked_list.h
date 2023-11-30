//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/memory/pool.h"


namespace cobalt {
    /* A linked list implementation.
     */
    template<typename T>
    class LinkedList {
        public:
        /* Creates a new linked list.
         * @return: The new linked list.
         */
        LinkedList() : head(nullptr), tail(nullptr), size(0), pool(1) {}
        /* Destroys the linked list.
         */
        ~LinkedList() {
            Node* node = head;
            while (node != nullptr) {
                Node* next = node->next;
                pool.drop(node);
                node = next;
            }
        }
        
        /* Push an element to the tail end of the list.
         * @param data: The data to insert.
         */
        void push(const T& data) {
            Node* node = (Node*) pool.grab();
            *node = createNode(data);
            if (head == nullptr) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
            size++;
        }
        /* Emplace an element at the tail end of the list.
         * @param args: The arguments to forward to the constructor.
         */
        template <typename... Args>
        void emplace(Args&&... args) {
            push(T(std::forward<Args>(args)...));
        }
        /* Removes the element at the tail end of the list.
         * @return: The element at the tail end of the list.
         */
        T pop() {
            T data = tail->data;
            remove(size - 1);
            return data;
        }
        /* Removes the element at the given index.
         * @param index: The index of the element to remove.
         */
        void remove(const uint index) {
            if (index < 0 || index >= size) {
                throw std::runtime_error("Index out of bounds");
            }

            Node *node = head;
            Node *prev = NULL;
            for (int i = 0; i < index; i++) {
                prev = node;
                node = node->next;
            }
            if (prev == NULL) head = node->next;
            else prev->next = node->next;
            if (node == tail)
                tail = prev;

            pool.drop(node);
            size--;
        }
        /* Inserts an element after the given index.
         * @param index: The index to insert after.
         * @param data: The data to insert.
         */
        void insertAfter(const uint index, const T& data) {
            if (index >= size) {
                throw std::runtime_error("Index out of bounds");
            }
            Node* node = head;
            for (uint i = 0; i < index; i++) {
                node = node->next;
            }
            Node* next = node->next;
            Node* new_node = pool.grab();
            *new_node = createNode(data);
            node->next = new_node;
            new_node->next = next;
            size++;
        }
        /* Gets the element at the given index.
         * @param index: The index of the element to get.
         * @return: The element at the given index.
         */
        T get(const uint index) const {
            if (index >= size) {
                throw std::runtime_error("Index out of bounds");
            }
            Node* node = head;
            for (uint i = 0; i < index; i++) {
                node = node->next;
            }
            return node->data;
        }
        /* Gets the number of elements in the list.
         * @return: The size of the list.
         */
        uint getSize() const { return size; }

        private:
        struct Node {
            T data;                 // The data stored in the node.
            Node* next;             // The next node in the list.
        };

        PoolAllocator<Node> pool;   // The allocator used to allocate nodes.
        Node* head;                 // The first node in the list.
        Node* tail;                 // The last node in the list.
        uint size;                  // The number of nodes in the list.
    
        /* Creates a new node.
         * @param data: The data to store in the node.
         * @return: The new node.
         */
        Node createNode(const T& data) const {
            return {
                .data = data,
                .next = nullptr
            };
        }
    };
}