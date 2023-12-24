//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/memory/heap.h"


namespace cobalt {
    namespace core {
        /** An arena allocator is a memory allocator that allocates
        * memory in variable-sized blocks. It is useful for allocating many objects
        * of different types (e.g. entities in an ECS) that are not freed individually.
        */
        class ArenaAllocator : public Allocator {
            public:
            /** Creates an arena allocator with a given initial size.
            * @param initial_size: The initial size of the arena.
            */
            ArenaAllocator(const size_t initial_size);
            /** Destroys an arena allocator.
            */
            ~ArenaAllocator();

            /** Allocates a block of memory from the arena.
            * @param size: The size of the block to allocate.
            * @return: A pointer to the allocated block.
            */
            void* grab(const size_t size);
            /** Resizes a block of memory from the arena.
            * Since the arena allocator does not resize individual blocks,
            * this function simply allocates a new block.
            * Calling this multiple times will result in memory leaks.
            * @param ptr: The pointer to the block to resize.
            * @param size: The new size of the block.
            * @return: A pointer to the resized block.
            */
            void* resize(void* ptr, const size_t size);
            /** Calculate the allocated size of the arena.
            * @return: The allocated size of the arena in bytes.
            */
            size_t getSize();

            private:
            struct ArenaBlock {
                size_t block_size;      // The current allocated size in bytes of the block.
                size_t block_capacity;  // The capacity in bytes of the block.
                void* data;             // The data of the block.
            };

            HeapAllocator heap;         // The heap allocator of the arena.
            ArenaBlock* blocks;         // The blocks of the arena.
            uint block_count;           // The number of blocks in the arena.
            size_t arena_size;          // The size of the arena.

            /** Allocates a block of memory from the arena.
            * @param size: The size of the block to allocate.
            * @return: A pointer to the allocated block.
            */
            void* alloc(const size_t size) override;
            /** Frees a block of memory from the arena.
            * Since the arena allocator does not free individual blocks,
            * this function throws an error.
            * @param ptr: The pointer to the block to free.
            */
            void free(void* ptr) override;
            /** Resizes a block of memory from the arena.
            * Since the arena allocator does not resize individual blocks,
            * this function simply allocates a new block.
            * Calling this multiple times will result in memory leaks.
            * @param ptr: The pointer to the block to resize.
            * @param size: The new size of the block.
            * @return: A pointer to the resized block.
            */
            void* realloc(void* ptr, const size_t size) override;

            /** Creates an arena block with a given size.
            * @param heap: The heap allocator of the arena.
            * @param size: The size of the block to create.
            * @return: The created arena block.
            */
            ArenaBlock arenaBlockCreate(HeapAllocator& heap, const size_t size);
            /** Destroys an arena block.
            * @param heap: The heap allocator of the arena.
            * @param block: The block to destroy.
            */
            void arenaBlockDestroy(HeapAllocator& heap, ArenaBlock *block);
        };
    }
}