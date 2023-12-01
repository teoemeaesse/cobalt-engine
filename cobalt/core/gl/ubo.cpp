//
// Created by tomas on 30-11-2023.
//

#include "core/gl/ubo.h"


namespace cobalt {
    namespace core {
        UBO::UBO(const GLUsage usage, const size_t size) : usage(usage), size(size) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
            glBufferData(GL_UNIFORM_BUFFER, size, nullptr, (GLenum) usage);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        UBO::~UBO() {
            glDeleteBuffers(1, &buffer);
        }

        void UBO::bind() const {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer);
        }

        void UBO::unbind() const {
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void UBO::setBindingPoint(const GLHandle shader, const GLHandle bindingPoint) const {
            glUniformBlockBinding(shader, bindingPoint, bindingPoint);
            glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
        }

        void UBO::load(const void* data, const size_t size) const {
            glBufferData(GL_UNIFORM_BUFFER, size, data, (GLenum) usage);
        }

        void UBO::load(const void* data, const size_t size, const size_t offset) const {
            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
        }
    }
}