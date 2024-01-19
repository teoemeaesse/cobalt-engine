// Created by tomas on
// 30-11-2023

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        /** @brief: Vertex buffer object, used to store vertex data.
         */
        class VBO {
            public:
            /** @brief: Creates a vertex buffer object.
             * @param usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
             * @return: VBO.
             */
            VBO(const gl::Usage usage);
            /** @brief: Destroys the VBO.
             */
            ~VBO();
            /** @brief: Copy constructor.
             * @param other: The VBO to copy.
             * @return: VBO.
             */
            VBO(const VBO&);
            /** @brief: Move constructor.
             * @param vbo: The VBO to move.
             * @return: VBO.
             */
            VBO(VBO&&) noexcept;
            /** @brief: Copy assignment operator.
             * @param other: The VBO to copy.
             * @return: The copied VBO.
             */
            VBO& operator=(const VBO&);
            /** @brief: Move assignment operator.
             * @param other: The VBO to move.
             * @return: The moved VBO.
             */
            VBO& operator=(VBO&&) noexcept;

            /** @brief: Binds the VBO to the current context.
             */
            void bind() const;
            /** @brief: Unbinds the VBO from the current context.
             */
            void unbind() const;
            /** @brief: Reserves space in the VBO. Bind before calling.
             * @param size: The number of bytes to reserve.
             */
            void reserve(const size_t size) const;
            /** @brief: Loads data into the VBO. Bind before calling.
             * @param data: The data to load.
             * @param size: The size of the data to load in bytes.
             */
            void load(const void* data, const size_t size) const;
            /** @brief: Loads a subset of data into the VBO. Bind before calling.
             * @param data: The data to load.
             * @param size: The size of the data to load in bytes
             * @param offset: The offset into the data in bytes..
             */
            void load(const void* data, const size_t size, const size_t offset) const;

            private:
            gl::Handle buffer;  // The OpenGL buffer handle.
            gl::Usage usage;    // The usage of the buffer.
        };
    }  // namespace core::gl
}  // namespace cobalt