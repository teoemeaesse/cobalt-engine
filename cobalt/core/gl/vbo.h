/**
 * @file vbo.h
 * @brief Vertex Buffer Object (VBO) class for storing vertex data in OpenGL buffers. This class manages the resources associated with VBOs,
 * @author Tomás Marques
 * @date 30-11-2023
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief Vertex Buffer Object, used to store and manage vertex data.
         */
        class VBO {
            public:
            /**
             * @brief Creates a vertex buffer object.
             * @param usage gl::Usage::StaticDraw, gl::Usage::DynamicDraw, or gl::Usage::StreamDraw.
             */
            VBO(const gl::Usage usage);
            /**
             * @brief Destroys the VBO.
             */
            ~VBO();
            /**
             * @brief Copy constructor.
             * @param other The VBO to copy.
             */
            VBO(const VBO&);
            /**
             * @brief Move constructor.
             * @param vbo The VBO to move.
             */
            VBO(VBO&&) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The VBO to copy.
             */
            VBO& operator=(const VBO&);
            /**
             * @brief Move assignment operator.
             * @param other The VBO to move.
             */
            VBO& operator=(VBO&&) noexcept;

            /**
             * @brief Binds the VBO to the current context.
             */
            void bind() const;
            /**
             * @brief Unbinds the VBO from the current context.
             */
            void unbind() const;

            /**
             * @brief Reserves space in the VBO. Bind before calling.
             * @param size The number of bytes to reserve.
             */
            void reserve(const size_t size) const;

            /**
             * @brief Loads data into the VBO. Bind before calling.
             * @param data The data to load.
             * @param size The size of the data to load in bytes.
             */
            void load(const void* data, const size_t size) const;
            /**
             * @brief Loads a subset of data into the VBO. Bind before calling.
             * @param data The data to load.
             * @param size The size of the data to load in bytes.
             * @param offset The offset into the data in bytes.
             */
            void load(const void* data, const size_t size, const size_t offset) const;

            private:
            gl::Handle buffer;  ///< The OpenGL buffer handle.
            gl::Usage usage;    ///< The usage of the buffer.
        };
    }  // namespace core::gl
}  // namespace cobalt