//
// Created by tomas on 28-11-2023.
//

#include "core/memory/heap.h"


// TODO: Implement custom heap allocator.

void *cobalt::HeapAllocator::alloc(const size_t size) {
    return (void *) malloc(size);
}

void cobalt::HeapAllocator::free(void *ptr) {
    ::free(ptr);
}

void *cobalt::HeapAllocator::realloc(void *ptr, const size_t size) {
    return (void *) realloc(ptr, size);
}