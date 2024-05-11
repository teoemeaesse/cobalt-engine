/**
 * @file ubo.h
 * @brief Uniform Buffer Object (UBO) class. Wraps around OpenGL UBOs.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#pragma once

#include "core/gl/shader.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief A Uniform Buffer Object (UBO). Used to store uniform data that is shared between multiple shaders.
         */
        class UBO {
            public:
            /**
             * @brief Creates a UBO.
             * @param usage GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
             * @param size The size of the buffer in bytes.
             */
            UBO(const gl::Usage usage, const size_t size);
            /**
             * @brief Destroys the UBO and releases any resources allocated by OpenGL.
             */
            ~UBO();

            /**
             * @brief Binds the UBO to the current context.
             */
            void bind() const;
            /**
             * @brief Use the UBO in a shader.
             * @param shader The shader to bind to.
             * @param name The name of the uniform block.
             * @param binding The binding point of the uniform block. This must match the binding in the shader.
             */
            void bindToShader(const Shader& shader, const std::string& name, const uint binding) const;
            /**
             * @brief Unbinds the UBO from the current context.
             */
            void unbind() const;
            /**
             * @brief Sets the data of the entire buffer. Bind before calling.
             * @param data The data to load.
             * @param size The size of the data in bytes.
             */
            void load(const void* data, const size_t size) const;
            /**
             * @brief Sets the data of a specific uniform or uniform block. Bind before calling.
             * @param data The data to load.
             * @param size The size of the data in bytes.
             * @param offset The offset in bytes from the start of the buffer.
             */
            void load(const void* data, const size_t size, const size_t offset) const;

            private:
            gl::Handle buffer;      ///< The OpenGL buffer handle.
            const gl::Usage usage;  ///< The usage of the buffer.
            const size_t size;      ///< The size of the buffer in bytes.
        };
    }  // namespace core::gl
}  // namespace cobalt