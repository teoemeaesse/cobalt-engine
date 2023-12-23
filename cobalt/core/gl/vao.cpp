//
// Created by tomas on 01-12-2023.
//

#include "core/gl/vao.h"


namespace cobalt {
    namespace core {
        void VAOLayout::push(const GLType type, const uint count, const bool normalized) {
            attributes.push({count, type, normalized, stride});
            stride += count * getGLTypeSize(type);
        }

        size_t VAOLayout::getStride() const {
            return stride;
        }

        VAO::VAO(const VBO& vbo, const VAOLayout& layout) {
            glGenVertexArrays(1, &buffer);
            glBindVertexArray(buffer);
            vbo.bind();
            for (uint i = 0; i < layout.attributes.getSize(); i++) {
                const auto& attribute = layout.attributes.get(i);
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, attribute.count, (GLenum) attribute.type, attribute.normalized, layout.stride, (void*) attribute.stride);
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

        void VAO::bind() const {
            glBindVertexArray(buffer);
        }

        void VAO::unbind() const {
            glBindVertexArray(0);
        }
    }
}