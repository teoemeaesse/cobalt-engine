//
// Created
// by
// tomas
// on
// 29-11-2023.
//

#include "core/memory/arena.h"

#include <cstring>

namespace cobalt {
    namespace core::memory {
        ArenaAllocator::ArenaAllocator(const size_t initial_size) : heap(), block_count(1), arena_size(0) {
            blocks = (ArenaBlock*)heap.grab(sizeof(ArenaBlock));
            blocks[0] = arenaBlockCreate(heap, initial_size);
        }

        ArenaAllocator::~ArenaAllocator() {
            for (uint i = 0; i < block_count; i++) {
                arenaBlockDestroy(heap, &blocks[i]);
            }
            heap.drop(blocks);
        }

        void* ArenaAllocator::grab(const size_t size) {
            arena_size += size;
            for (uint i = 0; i < block_count; i++) {
                if (blocks[i].block_size + size < blocks[i].block_capacity) {
                    void* ptr = (void*)((char*)blocks[i].data + blocks[i].block_size);
                    blocks[i].block_size += size;
                    return ptr;
                }
            }
            blocks = (ArenaBlock*)heap.resize(blocks, (block_count + 1) * sizeof(ArenaBlock));
            blocks[block_count] = arenaBlockCreate(heap, ArenaAllocator::getSize());
            void* ptr = (void*)((char*)blocks[block_count].data + blocks[block_count].block_size);
            blocks[block_count++].block_size += size;
            return ptr;
        }

        void* ArenaAllocator::resize(void* ptr, const size_t size) {
            void* new_ptr = grab(size);
            memcpy(new_ptr, ptr, size);
            return new_ptr;
        }

        size_t ArenaAllocator::getSize() { return arena_size; }

        void* ArenaAllocator::alloc(const size_t size) { return grab(size); }

        void ArenaAllocator::free(void* ptr) {
            // Do nothing.
        }

        void* ArenaAllocator::realloc(void* ptr, const size_t size) { return resize(ptr, size); }

        ArenaAllocator::ArenaBlock ArenaAllocator::arenaBlockCreate(HeapAllocator& heap, const size_t size) {
            ArenaBlock block;
            block.block_size = 0;
            block.block_capacity = size;
            block.data = heap.grab(size);
            return block;
        }

        void ArenaAllocator::arenaBlockDestroy(HeapAllocator& heap, ArenaBlock* block) { heap.drop(block->data); }
    }  // namespace core
} // namespace cobalt