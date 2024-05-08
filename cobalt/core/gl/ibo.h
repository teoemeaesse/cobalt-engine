/**
 * @file ibo.h
 * @brief Index Buffer Object (IBO) class for indexed rendering in OpenGL.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief Represents an Index Buffer Object used for indexed rendering in OpenGL.
         * This class encapsulates the functionality of OpenGL index buffers, allowing for efficient rendering of shared vertices by reusing them in
         * multiple primitives.
         */
        class IBO {
            public:
            /**
             * @brief Constructs an IBO with a specified number of indices.
             * @param usage Specifies the expected usage pattern of the data store (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW).
             * @param indexCount The number of indices in the IBO.
             */
            IBO(const gl::Usage usage, const uint indexCount);
            /**
             * @brief Constructs an IBO with initial data and a specified number of indices.
             * @param usage Specifies the expected usage pattern of the data store (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW).
             * @param indices A list of indices to copy into the IBO.
             * @param indexCount The number of indices in the IBO.
             */
            IBO(const gl::Usage usage, const uint* indices, const uint indexCount);
            /**
             * @brief Destructor that cleans up the IBO resources.
             */
            ~IBO();
            /**
             * @brief Copy constructor is deleted to prevent copying of IBO resources.
             */
            IBO(const IBO&) = delete;
            /**
             * @brief Move constructor to transfer ownership of IBO resources.
             * @param ibo The IBO to move.
             */
            IBO(IBO&&) noexcept;
            /**
             * @brief Copy assignment is deleted to prevent copying of IBO resources.
             */
            IBO& operator=(const IBO&) = delete;
            /**
             * @brief Move assignment operator to transfer ownership of IBO resources.
             * @param other The IBO to move.
             */
            IBO& operator=(IBO&&) noexcept;

            /**
             * @brief Binds this IBO to the current context.
             */
            void bind() const;
            /**
             * @brief Unbinds this IBO from the current context.
             */
            void unbind() const;

            /**
             * @brief Retrieves the number of indices in the IBO.
             * @return The number of indices.
             */
            const uint getCount() const;

            /**
             * @brief Creates an IBO optimized for rendering quads.
             * @param usage Specifies the expected usage pattern of the data store.
             * @param count The number of quads to be rendered.
             * @return A new IBO configured for rendering the specified number of quads.
             */
            static IBO fromQuads(const gl::Usage usage, const uint count);

            /**
             * @brief Creates an IBO optimized for rendering a cube.
             * @param usage Specifies the expected usage pattern of the data store.
             * @return A new IBO configured for rendering a cube.
             */
            static IBO fromCube(const gl::Usage usage);

            private:
            gl::Handle buffer;  ///< OpenGL buffer handle.
            gl::Usage usage;    ///< Specifies the usage pattern of the IBO.
            uint indexCount;    ///< Number of indices in the IBO.
        };

    }  // namespace core::gl
}  // namespace cobalt