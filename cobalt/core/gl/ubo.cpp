/**
 * @file ubo.cpp
 * @brief Uniform Buffer Object (UBO) class. Wraps around OpenGL UBOs.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#include "core/gl/ubo.h"

namespace cobalt {
    namespace core::gl {
        UBO::UBO(const gl::Usage usage, const size_t size) : usage(usage), size(size) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferData(GL_UNIFORM_BUFFER, size, nullptr, (GLenum)usage);
        }

        UBO::~UBO() { glDeleteBuffers(1, &buffer); }

        void UBO::bind() const { glBindBuffer(GL_UNIFORM_BUFFER, buffer); }

        void UBO::bindToShader(const Shader& shader, const std::string& name, const uint binding) const {
            glUniformBlockBinding(shader.getGLHandle(), shader.getUBIndex(name), binding);
            glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer);
        }

        void UBO::unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

        void UBO::load(const void* data, const size_t size) const { glBufferData(GL_UNIFORM_BUFFER, size, data, (GLenum)usage); }

        void UBO::load(const void* data, const size_t size, const size_t offset) const { glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data); }
    }  // namespace core::gl
}  // namespace cobalt