//
// Created by tomas on 28-11-2023.
//

#pragma once

#include "core/pch.h"


namespace cobalt {
    namespace core {
        class Allocator {
            public:
            virtual ~Allocator() = default;

            /* Allocates a block of memory.
            * @param size: The size of the block to allocate.
            * @return: A pointer to the allocated block.
            */
            virtual void* alloc(const size_t size) = 0;
            /* Frees a block of memory.
            * @param ptr: The pointer to the block to free.
            */
            virtual void free(void* ptr) = 0;
            /* Reallocates a block of memory.
            * @param ptr: The pointer to the block to reallocate.
            * @param size: The new size of the block.
            * @return: A pointer to the reallocated block.
            */
            virtual void* realloc(void* ptr, const size_t size) = 0;
        };
    }

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}