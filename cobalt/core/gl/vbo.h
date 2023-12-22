//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/pch.h"


namespace cobalt {
    namespace core {
        /* Vertex buffer object, used to store vertex data.
        */
        class VBO {
            public:
            /* Creates a vertex buffer object.
            * @param usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
            * @return: VBO.
            */
            VBO(const GLUsage usage);
            /* Destroys the VBO.
            */
            ~VBO();
            /* Copy constructor.
             * @param other: The VBO to copy.
             * @return: VBO.
             */
            VBO(const VBO&);
            /* Move constructor.
             * @param vbo: The VBO to move.
             * @return: VBO.
             */
            VBO(VBO&&) noexcept;
            /* Copy assignment operator.
             * @param other: The VBO to copy.
             * @return: The copied VBO.
             */
            VBO& operator=(const VBO&);
            /* Move assignment operator.
             * @param other: The VBO to move.
             * @return: The moved VBO.
             */
            VBO& operator=(VBO&&) noexcept;

            /* Binds the VBO to the current context.
            */
            void bind() const;
            /* Unbinds the VBO from the current context.
            */
            void unbind() const;
            /* Reserves space in the VBO. Bind before calling.
            * @param size: The number of bytes to reserve.
            */
            void reserve(const size_t size) const;
            /* Loads data into the VBO. Bind before calling.
            * @param data: The data to load.
            * @param size: The size of the data to load in bytes.
            */
            void load(const void* data, const size_t size) const;
            /* Loads a subset of data into the VBO. Bind before calling.
            * @param data: The data to load.
            * @param size: The size of the data to load in bytes
            * @param offset: The offset into the data in bytes..
            */
            void load(const void* data, const size_t size, const size_t offset) const;

            private:
            GLHandle buffer;        // The opengl buffer handle.
            GLUsage usage;          // The usage of the buffer.
        };
    }
}