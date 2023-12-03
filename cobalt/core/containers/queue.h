//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/memory/pool.h"
#include "core/exceptions/container_exception.h"


namespace cobalt {
    namespace core {
        /* A queue container. It is a FIFO (First In First Out) container.
         * No support for priority queues.
         */
        template <typename T>
        class Queue {
            public:
            /* Creates a queue enough to hold initial_capacity elements.
             * @param initial_capacity: The initial capacity of the queue.
             * @return: A queue with the initial capacity.
             */
            Queue(const uint initial_capacity = 16) : 
                pool(initial_capacity), head(nullptr), tail(nullptr), size(0) {}
            /* Destroys the queue
             */
            ~Queue() {
                if (head != nullptr) {
                    Node* node = head;
                    while (node != nullptr) {
                        Node* next = node->next;
                        pool.drop(node);
                        node = next;
                    }
                }
            }

            /* Pushes an element to the queue.
             * @param element: The element to push.
             */
            void enqueue(const T& element) {
                Node* node = pool.grab();
                node->data = element;
                node->next = nullptr;
                if (head == nullptr) {
                    head = node;
                    tail = node;
                } else {
                    tail->next = node;
                    tail = node;
                }
                size++;
            }

            /* Pops an element from the queue.
             * @return: The element popped from the queue.
             */
            T dequeue() {
                if (head == nullptr) {
                    throw ContainerException("Queue is empty");
                }
                Node* node = head;
                head = head->next;
                T data = node->data;
                pool.drop(node);
                size--;
                return data;
            }

            const uint getSize() const {
                return size;
            }

            private:
            struct Node {
                T data;         // The data of the node.
                Node* next;     // The next node in the queue.
            };
            PoolAllocator<Node> pool;   // The pool allocator for the queue.
            Node* head;                 // The head of the queue.
            Node* tail;                 // The tail of the queue.
            uint size;                  // The size of the queue.
        };
    }
}