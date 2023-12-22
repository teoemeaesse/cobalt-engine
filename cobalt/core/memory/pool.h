//
// Created by tomas on 28-11-2023.
//

#pragma once

#include "core/memory/heap.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
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
            PoolAllocator(const uint block_capacity) : heap(), chunk_count(1), block_count(0) {
                chunks = (PoolChunk*) heap.grab(sizeof(PoolChunk));
                chunks[0] = poolChunkCreate(heap, block_capacity);
            }
            /* Destroys a pool allocator.
            */
            ~PoolAllocator() {
                for (uint i = 0; i < chunk_count; i++) {
                    poolChunkDestroy(heap, &chunks[i]);
                }
                heap.drop(chunks);
            }

            /* Allocates a block of memory from the pool.
            * @return: A pointer to the allocated block.
            */
            T* grab() {
                block_count++;
                for (uint i = 0; i < chunk_count; i++) {
                    if (chunks[i].block_count < chunks[i].block_capacity) {
                        uint index = chunks[i].free_blocks[chunks[i].block_count++];
                        return (T*) ((char*) chunks[i].data + index * sizeof(T));
                    }
                }
                chunks = (PoolChunk*) heap.resize(chunks, (chunk_count + 1) * sizeof(PoolChunk));
                chunks[chunk_count++] = poolChunkCreate(heap, PoolAllocator<T>::getSize());
                return (T*) ((char*) chunks[chunk_count - 1].data + chunks[chunk_count - 1].block_count++ * sizeof(T));
            }
            /* Frees a block of memory from the pool.
            * @param ptr: The pointer to the block to free.
            */
            void drop(T* ptr) {
                block_count--;
                for (uint i = 0; i < chunk_count; i++) {
                    if (ptr >= (T*) chunks[i].data && ptr < (T*) ((char*) chunks[i].data + chunks[i].block_capacity * sizeof(T))) {
                        chunks[i].free_blocks[--chunks[i].block_count] = (uint) ((char*) ptr - (char*) chunks[i].data) / sizeof(T);
                        return;
                    }
                }
            }
            /* Calculate the allocated size of the pool.
            * @return: The allocated size of the pool in bytes.
            */
            size_t getSize() {
                return block_count * sizeof(T);
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
            uint block_count;           // The number of blocks allocated by the pool.
            
            /* Allocates a block of memory from the pool.
            * @param size: The size of the block to allocate. This parameter is ignored.
            * @return: A pointer to the allocated block.
            */
            void* alloc(const size_t size) override {
                return grab();
            }
            /* Frees a block of memory from the pool.
            * @param ptr: The pointer to the block to free.
            */
            void free(void* ptr) override {
                drop((T*) ptr);
            }
            /* Reallocates a block of memory from the pool.
            * Since the pool allocator does not support variable block sizes, this
            * function simply throws an error.
            * @param ptr: The pointer to the block to reallocate.
            * @return: A pointer to the reallocated block.
            */
            void *realloc(void* ptr, const size_t size) override {
                return nullptr;
            }
            /* Creates a pool chunk with a given block capacity.
            * @param block_capacity: The number of blocks in the chunk.
            * @return: The created chunk.
            */
            PoolChunk poolChunkCreate(HeapAllocator& heap, const uint block_capacity) {
                PoolChunk chunk = {
                    .data = heap.grab(block_capacity * sizeof(T)),
                    .free_blocks = (uint*) heap.grab(block_capacity * sizeof(uint)),
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
            void poolChunkDestroy(HeapAllocator& heap, PoolChunk* chunk) {
                heap.drop(chunk->data);
                heap.drop(chunk->free_blocks);
            }
        };
    }
}