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
         * @brief A Uniform Buffer Object (UBO) is used to store uniform data that is shared between multiple shaders.
         * This class should be used to interface with UBO's. To create a custom UBO, see ConcreteUBO.
         * @see ConcreteUBO
         */
        class UBO {
            public:
            /**
             * @brief Creates a UBO.
             * @param usage One of cobalt::core::gl::StaticDraw, cobalt::core::gl::DynamicDraw, cobalt::core::gl::StreamDraw.
             * @param capacity The maximum size of the buffer (in bytes).
             */
            UBO(const gl::Usage usage, const size_t capacity);
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
             * @brief Copies an element into the end of the buffer.
             * @tparam T The element type.
             * @param element The element to push.
             * @throws
             */
            template <typename T>
            void push(const T* element) {
                if (size + sizeof(T) > capacity) {
                    // TODO: throw
                }
                glBufferSubData(GL_UNIFORM_BUFFER, size, sizeof(T), (void*)element);
                size += sizeof(T);
            }
            /**
             * @brief Constructs an element into the end of the buffer.
             * @tparam T The element type.
             * @tparam ...Args The types of the arguments to pass to the constructor.
             * @param args The arguments to pass to the constructor.
             */
            template <typename T, typename... Args>
            void emplace(Args&&... args) {
                T element(std::forward<Args>(args)...);
                if (size + sizeof(T) > capacity) {
                    // TODO: throw
                }
                glBufferSubData(GL_UNIFORM_BUFFER, size, sizeof(T), (void*)&element);
                size += sizeof(T);
            }

            /**
             * @brief Resets the buffer's data, maintaining its capacity.
             */
            virtual void clear();

            /**
             * @brief Resizes the buffer. This will overwrite any data in the buffer.
             * @param newCapacity The new maximum size of the buffer (in bytes).
             */
            virtual void resize(const size_t newCapacity);

            /**
             * @brief Adds any final metadata to the buffer before usage.
             */
            virtual void send();

            protected:
            gl::Handle buffer;      ///< The OpenGL buffer handle.
            const gl::Usage usage;  ///< The usage of the buffer.
            size_t capacity;        ///< The maximum size of the buffer (in bytes).
            size_t size;            ///< The current size of the buffer (in bytes).
        };
    }  // namespace core::gl
}  // namespace cobalt
