//
// Created by tomas on 28-11-2023.
//

#include "core/memory/heap.h"

// TODO: Implement custom heap allocator.

void *cobalt::HeapAllocator::grab(const size_t size) {
    return malloc(size);
}

void cobalt::HeapAllocator::drop(void *ptr) {
    ::free(ptr);
}

void *cobalt::HeapAllocator::resize(void *ptr, const size_t size) {
    return ::realloc(ptr, size);
}

void *cobalt::HeapAllocator::alloc(const size_t size) {
    return grab(size);
}

void cobalt::HeapAllocator::free(void *ptr) {
    drop(ptr);
}

void *cobalt::HeapAllocator::realloc(void *ptr, const size_t size) {
    return resize(ptr, size);
}
