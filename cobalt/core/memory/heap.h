// Created by tomas on
// 28-11-2023

#pragma once

#include "core/memory/allocator.h"

namespace cobalt {
    namespace core::memory {
        class HeapAllocator : public Allocator {
            public:
            HeapAllocator() = default;
            ~HeapAllocator() = default;

            /**
             * @brief: Allocates a block of memory from the heap.
             * @param size: The size in bytes of the block to allocate.
             * @return: A pointer to the allocated block.
             */
            void* grab(const size_t size);
            /**
             * @brief: Frees a block of memory from the heap.
             * @param ptr: A pointer to the block to free.
             * @return: void
             */
            void drop(void* ptr);
            /**
             * @brief: Reallocates a block of memory from the heap.
             * @param ptr: A pointer to the block to reallocate.
             * @param size: The size in bytes of the block to reallocate.
             */
            void* resize(void* ptr, const size_t size);

            private:
            /**
             * @brief: Allocates a block of memory from the heap.
             * @param size: The size in bytes of the block to allocate.
             * @return: A pointer to the allocated block.
             */
            void* alloc(const size_t size) override;
            /**
             * @brief: Frees a block of memory from the heap.
             * @param ptr: A pointer to the block to free.
             * @return: void
             */
            void free(void* ptr) override;
            /**
             * @brief: Reallocates a block of memory from the heap.
             * @param ptr: A pointer to the block to reallocate.
             * @param size: The size in bytes of the block to reallocate.
             * @return: A pointer to the reallocated block.
             */
            void* realloc(void* ptr, const size_t size) override;
        };
    }  // namespace core::memory
}  // namespace cobalt