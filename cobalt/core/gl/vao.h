// Created by tomas on
// 01-12-2023

#pragma once

#include "core/gl/vbo.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief: VAO layout specifies the format of the vertex data.
         * It is a list of vertex attributes and their layout.
         */
        class VAOLayout {
            friend class VAO;

            public:
            /**
             * @brief: Creates a VAO layout.
             */
            VAOLayout() : stride(0){};
            /**
             * @brief: Destroys the VAO layout.
             */
            ~VAOLayout() = default;

            /**
             * @brief: Push a vertex attribute to the VAO layout.
             * @param type: The type of the attribute.
             * @param count: The number of elements in the attribute.
             * @param normalized: Whether the attribute should be normalized.
             * @return: void
             */
            void push(const gl::Type type, const uint count, const bool normalized);

            /**
             * @brief: Get the stride of the vertex layout.
             * @return: The stride of the vertex layout.
             */
            size_t getStride() const;

            private:
            struct Attribute {
                uint count;       // The number of elements in the attribute.
                gl::Type type;    // The type of the elements in the attribute.
                bool normalized;  // Whether the attribute should be normalized.
                size_t stride;    // The stride of the attribute.

                /**
                 * @brief: Creates an attribute.
                 * @param count: The number of elements in the attribute.
                 * @param type: The type of the elements in the attribute.
                 * @param normalized: Whether the attribute should be normalized.
                 * @param stride: The stride of the attribute.
                 * @return: An attribute.
                 */
                Attribute(const uint count, const gl::Type type, const bool normalized, const size_t stride)
                    : count(count), type(type), normalized(normalized), stride(stride) {}
            };

            List<Attribute> attributes;  // The list of attributes.
            size_t stride;               // The current stride of the vertex data.
        };

        /**
         * @brief: Vertex Array Object (VAO) specifies the format of the vertex data as well as
         * the vertex buffer objects (VBOs) that contain the vertex data.
         */
        class VAO {
            public:
            /**
             * @brief: Creates a VAO from a VBO and a VAO layout.
             * The VAO layout specifies the format of the vertex data.
             * The VBO contains the vertex data.
             * @param vbo: The VBO containing the vertex data.
             * @param layout: The VAO layout specifying the format of the vertex data.
             * @return: A VAO.
             */
            VAO(const VBO& vbo, const VAOLayout& layout);
            /**
             * @brief: Destroys the VAO.
             */
            ~VAO();
            /**
             * @brief: Copy constructor.
             * @param other: The VAO to copy.
             * @return: A VAO.
             */
            VAO(const VAO& other) = delete;
            /**
             * @brief: Move constructor.
             * @param other: The VAO to move.
             * @return: A VAO.
             */
            VAO(VAO&& other) noexcept;
            /**
             * @brief: Copy assignment operator.
             * @param other: The VAO to copy.
             * @return: The copied VAO.
             */
            VAO& operator=(const VAO& other) = delete;
            /**
             * @brief: Move assignment operator.
             * @param other: The VAO to move.
             * @return: The moved VAO.
             */
            VAO& operator=(VAO&& other) noexcept;

            /**
             * @brief: Binds the VAO to the current OpenGL context.
             * @return: void
             */
            void bind() const;
            /**
             * @brief: Unbinds the VAO from the current OpenGL context.
             * @return: void
             */
            void unbind() const;

            private:
            gl::Handle buffer;  // The VAO handle.
        };
    }  // namespace core::gl
}  // namespace cobalt