//
// Created
// by
// tomas
// on
// 30-11-2023.
//

#include "core/gl/vbo.h"

namespace cobalt {
    namespace core {
        VBO::VBO(const GL::Usage usage) : usage(usage) { glGenBuffers(1, &buffer); }

        VBO::~VBO() {
            if (buffer != 0) {
                glDeleteBuffers(1, &buffer);
            }
        }

        VBO::VBO(VBO&& other) noexcept : usage(other.usage) {
            this->buffer = other.buffer;
            other.buffer = 0;
        }

        VBO& VBO::operator=(VBO&& other) noexcept {
            if (this != &other) {
                this->usage = other.usage;
                this->buffer = other.buffer;
                other.buffer = 0;
            }
            return *this;
        }

        void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, buffer); }

        void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

        void VBO::reserve(const size_t size) const { glBufferData(GL_ARRAY_BUFFER, size, nullptr, (GLenum)usage); }

        void VBO::load(const void* data, const size_t size) const { glBufferData(GL_ARRAY_BUFFER, size, data, (GLenum)usage); }

        void VBO::load(const void* data, const size_t size, const size_t offset) const { glBufferSubData(GL_ARRAY_BUFFER, offset, size, data); }
    }  // namespace core
}  // namespace
   // cobalt