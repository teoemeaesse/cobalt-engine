/**
 * @file vao.cpp
 * @brief Vertex Array Object (VAO) specifies the format of the vertex data as well as the vertex buffer objects (VBOs) that contain the vertex data.
 * @author Tomás Marques
 * @date 01-12-2023
 */

#include "core/gl/vao.h"

namespace cobalt {
    namespace core::gl {
        void VAOLayout::push(const gl::Type type, const uint count, const bool normalized) {
            attributes.emplace_back(count, type, normalized, stride);
            stride += count * gl::getTypeSize(type);
        }

        size_t VAOLayout::getStride() const { return stride; }

        VAO::VAO(const VBO& vbo, const VAOLayout& layout) {
            glGenVertexArrays(1, &buffer);
            glBindVertexArray(buffer);
            vbo.bind();
            uint i = 0;
            for (const auto& attribute : layout.attributes) {
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i++, attribute.count, (GLenum)attribute.type, attribute.normalized, layout.stride, (void*)attribute.stride);
            }
            glBindVertexArray(0);
            vbo.unbind();
        }

        VAO::~VAO() {
            if (buffer != 0) {
                glDeleteVertexArrays(1, &buffer);
            }
        }

        VAO::VAO(VAO&& other) noexcept {
            buffer = other.buffer;
            other.buffer = 0;
        }

        VAO& VAO::operator=(VAO&& other) noexcept {
            buffer = other.buffer;
            other.buffer = 0;
            return *this;
        }

        void VAO::bind() const { glBindVertexArray(buffer); }

        void VAO::unbind() const { glBindVertexArray(0); }
    }  // namespace core::gl
}  // namespace cobalt