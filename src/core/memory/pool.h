//
// Created by tomas on 18-11-2023.
//

#pragma once

#include "core/memory/heap.h"


namespace cobalt {
    /* A pool allocator is a memory allocator that allocates
    * memory in blocks of a fixed size. It is useful for allocating many objects
    * of the same type (e.g. components in an ECS).
    */
    template <typename T>
    class PoolAllocator : public Allocator {
        public:
        /* Creates a pool allocator with a given block capacity and block count.
         * @param block_capacity: The number of blocks in the pool.
         */
        PoolAllocator(const uint block_capacity) : heap() {
            chunks = (PoolChunk *) heap.alloc(sizeof(PoolChunk));
            chunks[0] = poolChunkCreate(heap, block_capacity);
            chunk_count = 1;
        }
        /* Destroys a pool allocator.
         */
        ~PoolAllocator() {
            for (uint i = 0; i < chunk_count; i++) {
                poolChunkDestroy(heap, &chunks[i]);
            }
            heap.free(chunks);
        }

        /* Allocates a block of memory from the pool.
         * @return: A pointer to the allocated block.
         */
        T* grab() {
            for (uint i = 0; i < chunk_count; i++) {
                if (chunks[i].block_count < chunks[i].block_capacity) {
                    uint index = chunks[i].free_blocks[chunks[i].block_count++];
                    return (T *) ((uint8_t *) chunks[i].data + index * sizeof(T));
                }
            }
            PoolChunk *chunk = (PoolChunk *) heap.realloc(chunks, (chunk_count + 1) * sizeof(PoolChunk));
            chunk[chunk_count] = poolChunkCreate(heap, chunks[0].block_capacity);
            chunks = chunk;
            chunk_count++;
            return (T *) ((uint8_t *) chunks[chunk_count - 1].data + chunks[chunk_count - 1].block_count++ * sizeof(T));
        }
        /* Frees a block of memory from the pool.
         * @param ptr: The pointer to the block to free.
         */
        void drop(T *ptr) {
            for (uint i = 0; i < chunk_count; i++) {
                if (ptr >= (T *) chunks[i].data && ptr < (T *) ((uint8_t *) chunks[i].data + chunks[i].block_capacity * sizeof(T))) {
                    chunks[i].free_blocks[--chunks[i].block_count] = (uint) ((uint8_t *) ptr - (uint8_t *) chunks[i].data) / sizeof(T);
                    return;
                }
            }
        }

        private:
        struct PoolChunk {
            void *data;             // The data of the chunk.
            uint *free_blocks;      // The indices of the free blocks.
            uint block_count;       // The number of allocated blocks in the chunk.
            uint block_capacity;    // The maximum number of blocks in the chunk.
        };
        
        HeapAllocator heap;         // The allocator for the chunks.
        PoolChunk *chunks;          // The chunks of memory allocated by the pool.
        uint chunk_count;           // The number of chunks allocated by the pool.
        
        /* Allocates a block of memory from the pool.
         * @param size: The size of the block to allocate. This parameter is ignored.
         * @return: A pointer to the allocated block.
         */
        void *alloc(const size_t size) override {
            return grab();
        }
        /* Frees a block of memory from the pool.
         * @param ptr: The pointer to the block to free.
         */
        void free(void *ptr) override {
            drop((T *) ptr);
        }
        /* Reallocates a block of memory from the pool.
         * Since the pool allocator does not support variable block sizes, this
         * function simply throws an error.
         * @param ptr: The pointer to the block to reallocate.
         * @return: A pointer to the reallocated block.
         */
        void* realloc(void *ptr, const size_t size) override {
            return nullptr;
        }

        /* Creates a pool chunk with a given block capacity.
        * @param block_capacity: The number of blocks in the chunk.
        * @return: The created chunk.
        */
        PoolChunk poolChunkCreate(HeapAllocator heap, const uint block_capacity) {
            struct PoolChunk chunk = {
                .data = heap.alloc(block_capacity * sizeof(T)),
                .free_blocks = (uint *) heap.alloc(block_capacity * sizeof(uint)),
                .block_count = 0,
                .block_capacity = block_capacity
            };
            for (uint i = 0; i < block_capacity; i++) {
                chunk.free_blocks[i] = i;
            }
            return chunk;
        }

        /* Destroys a pool chunk.
        * @param chunk: The chunk to destroy.
        */
        void poolChunkDestroy(HeapAllocator heap, PoolChunk *chunk) {
            heap.free(chunk->data);
            heap.free(chunk->free_blocks);
        }
    };
}