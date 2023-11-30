//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/memory/heap.h"


namespace cobalt {
    template <typename T>
    class Stack {
        public:
        /* Creates a stack enough to hold initial_capacity elements.
         * @param initial_capacity: The initial capacity of the stack.
         * @return: A stack with the initial capacity.
         */
        Stack(const uint initial_capacity = 16) : heap(), element_count(0), block_count(1) {
            blocks = (StackBlock*) heap.grab(sizeof(StackBlock));
            blocks[0] = stackBlockCreate(initial_capacity);
        }
        /* Destroys the stack
         */
        ~Stack() {
            for (uint i = 0; i < block_count; i++) {
                stackBlockDestroy(blocks[i]);
            }
            heap.drop(blocks);
        }

        /* Pushes an element to the stack. If the stack is full, it will be resized to fit.
         * @param element: The element to push.
         */
        void push(const T& element) {
            if (blocks[block_count - 1].block_size == blocks[block_count - 1].block_capacity) {
                Stack<T>::resize();
            }
            element_count++;
            blocks[block_count - 1].data[blocks[block_count - 1].block_size] = T(element);
            blocks[block_count - 1].block_size++;
        }
        /* Employs an element to the stack. If the stack is full, it will be resized to fit.
         * @param args: The arguments for the element constructor.
         */
        template <typename... Args>
        void emplace(Args&&... args) {
            if (blocks[block_count - 1].block_size == blocks[block_count - 1].block_capacity) {
                Stack<T>::resize();
            }
            element_count++;
            blocks[block_count - 1].data[blocks[block_count - 1].block_size] = T(std::forward<Args>(args)...);
            blocks[block_count - 1].block_size++;
        }
        /* Pops an element from the stack.
         * @return: The element popped from the stack.
         */
        T pop() {
            if (element_count == 0) {
                throw std::runtime_error("Stack is empty");
            }
            element_count--;
            if (blocks[block_count - 1].block_size == 0) {
                stackBlockDestroy(blocks[--block_count]);
            }
            return blocks[block_count - 1].data[--blocks[block_count - 1].block_size];
        }
        /* Peeks the top element of the stack.
         * @return: The top element of the stack.
         */
        const T& peek() {
            if (element_count == 0) {
                throw std::runtime_error("Stack is empty");
            }
            if (blocks[block_count - 1].block_size == 0) {
                return blocks[block_count - 2].data[blocks[block_count - 2].block_size - 1];
            }
            return blocks[block_count - 1].data[blocks[block_count - 1].block_size - 1];
        }
        /* Gets the size of the stack.
         * @return: The number of elements in the stack.
         */
        const uint getSize() {
            return element_count;
        }
    
        private:
        struct StackBlock {
            T *data;                // Pointer to the data.
            uint block_size;        // Number of elements in the block.
            uint block_capacity;    // Number of elements the block can hold.
        };

        HeapAllocator heap;         // Heap allocator for the stack.
        StackBlock *blocks;         // Pointer to the blocks.
        uint block_count;           // Number of blocks in the stack.
        uint element_count;         // Number of elements in the stack.

        /* Creates a stack block with the given capacity.
         * @param capacity: The capacity of the block.
         * @return: A stack block with the given capacity.
         */
        StackBlock stackBlockCreate(const uint capacity) {
            return {
                .data = (T*) heap.grab(capacity * sizeof(T)),
                .block_size = 0,
                .block_capacity = capacity,
            };
        }
        /* Destroys a stack block.
         * @param block: The block to destroy.
         */
        void stackBlockDestroy(StackBlock& block) {
            heap.drop(block.data);
        }
        /* Resizes the stack to double its size.
         */
        void resize() {
            blocks = (StackBlock*) heap.resize(blocks, sizeof(StackBlock) * (block_count + 1));
            blocks[block_count] = stackBlockCreate(Stack<T>::getSize());
            block_count++;
        }
    };
}