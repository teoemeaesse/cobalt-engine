//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/memory/heap.h"
#include "core/exceptions/container_exception.h"


namespace cobalt {
    namespace core {
        template <typename T>
        class Stack {
            public:
            /* Creates a stack with an initial capacity.
             * @param initial_capacity: The initial capacity of the stack. Defaults to 16.
             * @return: A stack with the initial capacity.
             */
            Stack(const uint64 initial_capacity = 16) : heap(), element_count(0), block_count(1) {
                blocks = (StackBlock*) heap.grab(sizeof(StackBlock));
                blocks[0] = stackBlockCreate(initial_capacity);
            }
            /* Destroys the stack
             */
            ~Stack() {
                if (blocks == nullptr) {
                    return;
                }
                for (uint64 i = 0; i < block_count; i++) {
                    stackBlockDestroy(blocks[i]);
                }
                heap.drop(blocks);
            }
            /* Creates a new stack as a deep copy of another stack.
             * This constructor copies each element and block of the other stack
             * into a new stack, ensuring a complete copy of all data.
             * @param other: The stack to be copied.
             * @return: A new stack that is a deep copy of 'other'.
             */
            Stack(const Stack& other) :
                heap(),
                element_count(other.element_count),
                block_count(other.block_count),
                blocks(nullptr) {
                blocks = (StackBlock*) heap.grab(sizeof(StackBlock) * block_count);
                for (uint64 i = 0; i < block_count; ++i) {
                    blocks[i].data = (T*) heap.grab(other.blocks[i].block_capacity * sizeof(T));
                    blocks[i].block_size = other.blocks[i].block_size;
                    blocks[i].block_capacity = other.blocks[i].block_capacity;
                    std::copy(other.blocks[i].data, other.blocks[i].data + blocks[i].block_size, blocks[i].data);
                }
            }
            /* Creates a new stack by moving the resources of another stack.
             * This constructor takes ownership of the resources from 'other'
             * and leaves it in an empty state.
             * @param other: The stack whose resources are to be moved.
             * @return: A new stack containing the resources of 'other'.
             */
            Stack(Stack&& other) noexcept
                : heap(std::move(other.heap)), blocks(other.blocks), block_count(other.block_count), element_count(other.element_count) {
                other.blocks = nullptr;
                other.block_count = 0;
                other.element_count = 0;
            }
            /* Assigns a new value to the stack by copying another stack.
             * The current contents of the stack are cleared and replaced
             * with a deep copy of the contents of 'other'.
             * @param other: The stack to be copied.
             * @return: A reference to this stack after copying.
             */
            Stack& operator=(const Stack& other) {
                if (this != &other) {
                    for (uint64 i = 0; i < block_count; i++) {
                        stackBlockDestroy(blocks[i]);
                    }
                    heap.drop(blocks);
                    
                    element_count = other.element_count;
                    block_count = other.block_count;
                    blocks = (StackBlock*) heap.grab(sizeof(StackBlock) * block_count);
                    for (uint64 i = 0; i < block_count; ++i) {
                        blocks[i].data = (T*) heap.grab(other.blocks[i].block_capacity * sizeof(T));
                        blocks[i].block_size = other.blocks[i].block_size;
                        blocks[i].block_capacity = other.blocks[i].block_capacity;
                        std::copy(other.blocks[i].data, other.blocks[i].data + blocks[i].block_size, blocks[i].data);
                    }
                }
                return *this;
            }
            /* Assigns a new value to the stack by moving another stack.
             * The current contents of the stack are cleared and replaced
             * with the resources of 'other'. 'Other' is left in an empty state.
             * @param other: The stack whose resources are to be moved.
             * @return: A reference to this stack after moving.
             */
            Stack& operator=(Stack&& other) noexcept {
                if (this != &other) {
                    for (uint64 i = 0; i < block_count; i++) {
                        stackBlockDestroy(blocks[i]);
                    }
                    heap.drop(blocks);

                    heap = std::move(other.heap);
                    blocks = other.blocks;
                    block_count = other.block_count;
                    element_count = other.element_count;

                    other.blocks = nullptr;
                    other.block_count = 0;
                    other.element_count = 0;
                }
                return *this;
            }

            /* Adds an element to the top of the stack by copying it.
             * If the stack is full, it will be resized to fit.
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
            /* Adds an element to the top of the stack by moving it.
             * If the stack is full, it will be resized to fit.
             * @param element: The element to push.
             */
            void push(T&& element) {
                if (blocks[block_count - 1].block_size == blocks[block_count - 1].block_capacity) {
                    Stack<T>::resize();
                }
                element_count++;
                blocks[block_count - 1].data[blocks[block_count - 1].block_size] = T(std::move(element));
                blocks[block_count - 1].block_size++;
            }
            /* Constructs an element in-place at the top of the stack.
             * If the stack is full, it will be resized to fit.
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
            /* Removes and returns the top element of the stack.
             * @return: The element popped from the stack.
             */
            T pop() {
                if (element_count == 0) {
                    throw ContainerException("Stack is empty");
                }
                element_count--;
                if (blocks[block_count - 1].block_size == 0) {
                    stackBlockDestroy(blocks[--block_count]);
                }
                return blocks[block_count - 1].data[--blocks[block_count - 1].block_size];
            }
            /* Provides a reference to the top element of the stack.
             * @return: The top element of the stack.
             */
            const T& peek() const {
                if (element_count == 0) {
                    throw ContainerException("Stack is empty");
                }
                if (blocks[block_count - 1].block_size == 0) {
                    return blocks[block_count - 2].data[blocks[block_count - 2].block_size - 1];
                }
                return blocks[block_count - 1].data[blocks[block_count - 1].block_size - 1];
            }
            /* Gets the number of elements in the stack.
             * @return: The number of elements in the stack.
             */
            const uint64 getSize() const {
                return element_count;
            }
        
            private:
            struct StackBlock {
                T *data;                // Pointer to the data.
                uint64 block_size;      // Number of elements in the block.
                uint64 block_capacity;  // Number of elements the block can hold.
            };

            HeapAllocator heap;         // Heap allocator for the stack.
            StackBlock *blocks;         // Pointer to the blocks.
            uint64 block_count;         // Number of blocks in the stack.
            uint64 element_count;       // Number of elements in the stack.

            /* Creates a stack block with a specified capacity.
             * @param capacity: The capacity of the block.
             * @return: A stack block with the given capacity.
             */
            StackBlock stackBlockCreate(const uint64 capacity) {
                return {
                    .data = (T*) heap.grab(capacity * sizeof(T)),
                    .block_size = 0,
                    .block_capacity = capacity,
                };
            }
            /* Destroys a given stack block.
             * @param block: The block to destroy.
             */
            void stackBlockDestroy(StackBlock& block) {
                for (uint64 i = 0; i < block.block_size; i++) {
                    block.data[i].~T();
                }
                heap.drop(block.data);
            }
            /* Resizes the stack to accomodate more elements.
             */
            void resize() {
                blocks = (StackBlock*) heap.resize(blocks, sizeof(StackBlock) * (block_count + 1));
                blocks[block_count] = stackBlockCreate(Stack<T>::getSize());
                block_count++;
            }
        };
    }
}