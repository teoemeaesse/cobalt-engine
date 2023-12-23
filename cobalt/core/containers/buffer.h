//
// Created by tomas on 23-12-2023.
//

#pragma once

#include "core/memory/heap.h"


namespace cobalt {
    namespace core {
        /* A resizable buffer that you can keep pushing data into,
         * and then get a pointer to the data.
         */
        class Buffer {
            public:
            /* Create a buffer.
             * @param initialCapacity: The initial capacity of the buffer.
             */
            Buffer(size_t initialCapacity) :
                heap(HeapAllocator()),
                data(heap.grab(initialCapacity)),
                size(0),
                capacity(initialCapacity)
                {}
            /* Destroy the buffer.
             */
            ~Buffer() {
                heap.drop(data);
            }

            /* Push data into the buffer.
             * @param data: The data to push.
             */
            template <typename T>
            void push(const T& data) {
                if (this->size + sizeof(T) > this->capacity) {
                    this->capacity = this->capacity * 2 + sizeof(T);
                    this->data = this->heap.resize(this->data, this->capacity * 2);
                }
                new((T*)((char*) this->data + this->size)) T(data);
                this->size += sizeof(T);
            }
            /* Push data into the buffer.
             * @param data: The data to push.
             */
            template <typename T>
            void push(T&& data) {
                if (this->size + sizeof(T) > this->capacity) {
                    this->capacity = this->capacity * 2 + sizeof(T);
                    this->data = this->heap.resize(this->data, this->capacity * 2);
                }
                new((T*)((char*) this->data + this->size)) T(std::move(data));
                this->size += sizeof(T);
            }
            /* Push data into the buffer.
             * @param data: The data to push.
             * @param size: The size of the data to push.
             */
            void push(const void* data, size_t size) {
                if (this->size + size > this->capacity) {
                    this->capacity = this->capacity * 2 + size;
                    this->data = this->heap.resize(this->data, this->capacity * 2);
                }
                memcpy((char*) this->data + this->size, data, size);
                this->size += size;
            }

            /* Get a pointer to the data in the buffer.
             * @return: A pointer to the data in the buffer.
             */
            const void* getData() const {
                return this->data;
            }

            private:
            HeapAllocator heap; // The heap used to allocate the buffer.
            void* data;         // The data of the buffer.
            size_t size;        // The size of the buffer.
            size_t capacity;    // The capacity of the buffer.
        };
    }
}