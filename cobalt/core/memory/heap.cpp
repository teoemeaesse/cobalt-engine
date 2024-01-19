// Created by tomas on
// 28-11-2023

#include "core/memory/heap.h"

// TODO:
// Implement
// custom
// heap
// allocator.

namespace cobalt {
    namespace core::memory {
        void* HeapAllocator::grab(const size_t size) { return malloc(size); }

        void HeapAllocator::drop(void* ptr) { ::free(ptr); }

        void* HeapAllocator::resize(void* ptr, const size_t size) { return ::realloc(ptr, size); }

        void* HeapAllocator::alloc(const size_t size) { return grab(size); }

        void HeapAllocator::free(void* ptr) { drop(ptr); }

        void* HeapAllocator::realloc(void* ptr, const size_t size) { return resize(ptr, size); }
    }  // namespace core::memory
}  // namespace cobalt