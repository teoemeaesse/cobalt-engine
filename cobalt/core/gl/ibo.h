// Created by tomas on
// 30-11-2023

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief Index buffer object, used for indexed rendering.
         */
        class IBO {
            public:
            /**
             * @brief Creates an index buffer object.
             * @param usage GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
             * @param indexCount The number of indices.
             * @return IBO.
             */
            IBO(const gl::Usage usage, const uint indexCount);
            /**
             * @brief Creates an index buffer object with the given data.
             * @param usage GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
             * @param data The data.
             * @param indexCount The number of indices.
             */
            IBO(const gl::Usage usage, const uint* data, const uint indexCount);
            /**
             * @brief Destroys the IBO.
             */
            ~IBO();
            /**
             * @brief Copy constructor.
             * @param other The IBO to copy.
             * @return IBO.
             */
            IBO(const IBO&) = delete;
            /**
             * @brief Move constructor.
             * @param ibo The IBO to move.
             * @return IBO.
             */
            IBO(IBO&&) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The IBO to copy.
             * @return IBO.
             */
            IBO& operator=(const IBO&) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The IBO to move.
             * @return IBO.
             */
            IBO& operator=(IBO&&) noexcept;

            /**
             * @brief Binds the IBO to the current context.
             */
            void bind() const;
            /**
             * @brief Unbinds the IBO from the current context.
             */
            void unbind() const;
            /**
             * @brief Get the number of indices.
             * @return The number of indices.
             */
            const uint getCount() const;

            /**
             * @brief Create an IBO for n quads.
             * @param usage The usage of the buffer.
             * @param count The number of quads.
             */
            static IBO fromQuads(const gl::Usage usage, const uint count);
            /**
             * @brief Create an IBO for a cube.
             * @param usage The usage of the buffer.
             */
            static IBO fromCube(const gl::Usage usage);

            private:
            gl::Handle buffer;  // The OpenGL buffer handle.
            gl::Usage usage;    // The usage of the buffer.
            uint indexCount;    // The number of indices.
        };
    }  // namespace core::gl
}  // namespace cobalt