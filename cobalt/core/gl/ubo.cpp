/**
 * @file ubo.cpp
 * @brief Uniform Buffer Object (UBO) class. Wraps around OpenGL UBOs.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#include "core/gl/ubo.h"

namespace cobalt {
    namespace core::gl {
        UBO::UBO(const gl::Usage usage, const size_t capacity) : usage(usage), capacity(capacity), size(0) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferData(GL_UNIFORM_BUFFER, capacity, nullptr, (GLenum)usage);
        }

        UBO::~UBO() { glDeleteBuffers(1, &buffer); }

        void UBO::bind() const { glBindBuffer(GL_UNIFORM_BUFFER, buffer); }

        void UBO::bindToShader(const Shader& shader, const std::string& name, const uint binding) const {
            glUniformBlockBinding(shader.getGLHandle(), shader.getUBIndex(name), binding);
            glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer);
        }

        void UBO::clear() {
            glBufferData(GL_UNIFORM_BUFFER, capacity, nullptr, (GLenum)usage);
            size = 0;
        }

        void UBO::resize(const size_t newCapacity) { glBufferData(GL_UNIFORM_BUFFER, newCapacity, nullptr, (GLenum)usage); }

        void UBO::send() {
            // EMPTY - concrete implementations should extend this method.
        }
    }  // namespace core::gl
}  // namespace cobalt