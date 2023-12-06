//
// Created by tomas on 06-12-2023.
//

#pragma once

#include <cstring>

#include "core/containers/stack.h"


namespace cobalt {
    namespace core {
        template<typename T>
        class Vector {
            public:
            /* Creates a vector with the given initial capacity.
             * @param initialCapacity: The initial capacity of the vector.
             * @return: The created vector.
             */
            Vector(uint initialCapacity)
                : heap(HeapAllocator()),
                  data(heap.grab(initialCapacity * sizeof(T))),
                  indices((uint*) heap.grab(initialCapacity * sizeof(uint))),
                  capacity(initialCapacity),
                  size(0),
                  gaps(Stack<uint>(initialCapacity))
                {}
            /* Creates a vector, copied from another vector.
             * @param other: The vector to copy.
             * @return: The created vector.
             */
            Vector(const Vector<T>& other)
                : heap(HeapAllocator()),
                  data(heap.grab(other.capacity * sizeof(T))),
                  indices((uint*) heap.grab(other.capacity * sizeof(uint))),
                  capacity(other.capacity),
                  size(other.size),
                  gaps(other.gaps)
                {
                    memcpy(data, other.data, other.size * sizeof(T));
                    memcpy(indices, other.indices, other.size * sizeof(uint));
                }
            /* Destroys the vector.
             */
            ~Vector() {
                heap.drop(data);
                heap.drop(indices);
            }

            /* Copies the contents of another vector into this vector.
             * @param other: The vector to copy.
             * @return: This vector.
             */
            Vector<T>& operator=(const Vector<T>& other) {
                if (this != &other) {
                    return Vector<T>(other);
                }
                return *this;
            }

            /* Returns the element at the given index.
             * @param index: The index of the element.
             * @return: The element at the given index.
             */
            T& operator[](uint index) {
                return *(T*)((char*) data + indices[index] * sizeof(T));
            }
            /* Returns the element at the given index.
             * @param index: The index of the element.
             * @return: The element at the given index.
             */
            const T& operator[](uint index) const {
                return *(T*)((char*) data + indices[index] * sizeof(T));
            }

            /* Pushes an element to the end of the vector.
             * @param element: The element to push.
             */
            void push(const T& element) {
                if (gaps.getSize() > 0) {
                    uint index = gaps.pop();
                    indices[index] = size;
                    new((T*)((char*) data + index * sizeof(T))) T(element);
                } else {
                    if (size == capacity) {
                        resize(capacity * 2);
                    }
                    indices[size] = size;
                    new((T*)((char*) data + size * sizeof(T))) T(element);
                }
                size++;
            }
            /* Pushes an element to the end of the vector.
             * @param element: The element to push.
             */
            void push(T&& element) {
                if (gaps.getSize() > 0) {
                    uint index = gaps.pop();
                    indices[index] = size;
                    new((T*)((char*) data + index * sizeof(T))) T(std::move(element));
                } else {
                    if (size == capacity) {
                        resize(capacity * 2);
                    }
                    indices[size] = size;
                    new((T*)((char*) data + size * sizeof(T))) T(std::move(element));
                }
                size++;
            }
            /* Emplaces an element to the end of the vector.
             * @param args: The arguments for the element constructor.
             */
            template <typename... Args>
            void emplace(Args&&... args) {
                if (gaps.getSize() > 0) {
                    uint index = gaps.pop();
                    indices[index] = size;
                    new((T*)((char*) data + index * sizeof(T))) T(std::forward<Args>(args)...);
                } else {
                    if (size == capacity) {
                        resize(capacity * 2);
                    }
                    indices[size] = size;
                    new((T*)((char*) data + size * sizeof(T))) T(std::forward<Args>(args)...);
                }
                size++;
            }

            /* Removes the element at the given index.
             * @param index: The index of the element to remove.
             */
            void remove(uint index) {
                if (index >= size || size == 0 || index < 0) {
                    throw ContainerException("Index out of bounds");
                }
                ((T*)((char*) data + indices[index] * sizeof(T)))->~T();
                gaps.push(indices[index]);
                size--;
                for (uint i = index; i < size; i++) {
                    indices[i] = indices[i + 1];
                }
            }

            /* Returns the size of the vector.
             * @return: The size of the vector.
             */
            uint getSize() const {
                return size;
            }

            private:
            HeapAllocator heap;     // The heap allocator used to allocate the vector.
            void* data;             // The data of the vector.
            uint* indices;          // Maps each index to its corresponding block.
            uint capacity;          // The capacity of the vector.
            uint size;              // The size of the vector.
            Stack<uint> gaps;       // The gaps in the vector.

            /* Resizes the vector to the given capacity.
             * @param newCapacity: The new capacity of the vector.
             */
            void resize(uint newCapacity) {
                data = heap.resize(data, newCapacity * sizeof(T));
                indices = (uint*) heap.resize(indices, newCapacity * sizeof(uint));
                capacity = newCapacity;
            }
        };
    }
}