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
            Vector(uint initialCapacity) :
                heap(HeapAllocator()),
                data(heap.grab(initialCapacity * sizeof(T))),
                indices((uint*) heap.grab(initialCapacity * sizeof(uint))),
                capacity(initialCapacity),
                size(0),
                gaps(Stack<uint>(initialCapacity))
                {}
            /* Creates a new vector as a deep copy of another vector.
             * This constructor copies each element of the 'other' vector, preserving its state.
             * @param other: The vector to copy.
             * @return: The created vector.
             */
            Vector(const Vector<T>& other) :
                heap(HeapAllocator()),
                data(heap.grab(other.capacity * sizeof(T))),
                indices((uint*) heap.grab(other.capacity * sizeof(uint))),
                capacity(other.capacity),
                size(other.size),
                gaps(other.gaps) {
                for (uint i = 0; i < size; i++) {
                    new((T*)((char*) data + i * sizeof(T))) T(*(T*)((char*) other.data + i * sizeof(T)));
                    indices[i] = other.indices[i];
                }
            }
            /* Destroys the vector.
             */
            ~Vector() {
                if (data == nullptr) {
                    return;
                }
                for (uint i = 0; i < size; i++) {
                    ((T*)((char*) data + indices[i] * sizeof(T)))->~T();
                }
                heap.drop(data);
                heap.drop(indices);
            }
            /* Creates a new vector by moving the resources of another vector.
             * This constructor takes ownership of the resources from 'other' and leaves it in an empty state.
             * @param other: The vector to move.
             * @return: The created vector.
             */
            Vector(Vector<T>&& other) noexcept :
                heap(std::move(other.heap)),
                data(other.data),
                indices(other.indices),
                capacity(other.capacity),
                size(other.size),
                gaps(std::move(other.gaps)) {
                other.data = nullptr;
                other.indices = nullptr;
                other.capacity = 0;
                other.size = 0;
            }
            /* Assigns the contents of another vector to this vector.
             * This operation performs a deep copy of the 'other' vector's elements.
             * @param other: The vector to copy.
             * @return: This vector.
             */
            Vector<T>& operator=(const Vector<T>& other) {
                if (this != &other) {
                    clear(); // Clear current contents
                    // Allocate new resources
                    data = heap.grab(other.capacity * sizeof(T));
                    indices = (uint*) heap.grab(other.capacity * sizeof(uint));
                    capacity = other.capacity;
                    size = other.size;
                    gaps = other.gaps;
                    // Deep copy elements
                    for (uint i = 0; i < size; i++) {
                        new((T*)((char*) data + i * sizeof(T))) T(*(T*)((char*) other.data + i * sizeof(T)));
                        indices[i] = other.indices[i];
                    }
                }
                return *this;
            }
            Vector<T>& operator=(Vector<T>&& other) noexcept {
                if (this != &other) {
                    clear(); // Clear current contents
                    // Transfer ownership
                    heap = std::move(other.heap);
                    data = other.data;
                    indices = other.indices;
                    capacity = other.capacity;
                    size = other.size;
                    gaps = std::move(other.gaps);
                    // Leave 'other' in a valid, empty state
                    other.data = nullptr;
                    other.indices = nullptr;
                    other.capacity = 0;
                    other.size = 0;
                }
                return *this;
            }

            /* Returns the element at the given index.
             * @param index: The index of the element.
             * @return: The element at the given index.
             */
            T* raw(uint index) {
                if (index >= size || size == 0 || index < 0) {
                    throw ContainerException("Index out of bounds");
                }
                return (T*)((char*) data + indices[index] * sizeof(T));
            }

            /* Returns the element at the given index.
             * @param index: The index of the element.
             * @return: The element at the given index.
             */
            T& operator[](uint index) {
                if (index >= size || size == 0 || index < 0) {
                    throw ContainerException("Index out of bounds");
                }
                return *(T*)((char*) data + indices[index] * sizeof(T));
            }
            /* Returns the element at the given index.
             * @param index: The index of the element.
             * @return: The element at the given index.
             */
            const T& operator[](uint index) const {
                if (index >= size || size == 0 || index < 0) {
                    throw ContainerException("Index out of bounds");
                }
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

            /* Clears the vector.
             */
            void clear() {
                while (getSize() != 0) {
                    remove(0);
                }
            }

            private:
            HeapAllocator heap; // The heap allocator used to allocate the vector.
            void* data;         // The data of the vector.
            uint* indices;    // Maps each index to its corresponding block.
            uint capacity;    // The capacity of the vector.
            uint size;        // The size of the vector.
            Stack<uint> gaps; // The gaps in the vector.

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