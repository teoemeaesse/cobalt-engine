//
// Created by tomas on 30-11-2023.
//

#include "core/gl/ibo.h"
#include "core/utils/log.h"

namespace cobalt {
    namespace core {
        IBO::IBO(const GLUsage usage, const uint indexCount) : usage(usage), indexCount(indexCount) {
            glGenBuffers(1, &buffer);
        }

        IBO::~IBO() {
            if (buffer != 0) {
                glDeleteBuffers(1, &buffer);
                CB_WARN("IBO deleted");
            }
        }

        IBO::IBO(const IBO& other) : usage(other.usage), indexCount(other.indexCount) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_COPY_READ_BUFFER, other.buffer);
            glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
            GLint size;
            glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
            glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, (GLenum) usage);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
            CB_WARN("IBO copied");
        }

        IBO::IBO(IBO&& other) noexcept : usage(other.usage), indexCount(other.indexCount) {
            this->buffer = other.buffer;
            other.buffer = 0;
            CB_WARN("IBO moved");
        }

        IBO& IBO::operator=(const IBO& other) {
            if (this != &other) {
                this->usage = other.usage;
                this->indexCount = other.indexCount;
                glGenBuffers(1, &buffer);
                glBindBuffer(GL_COPY_READ_BUFFER, other.buffer);
                glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
                GLint size;
                glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
                glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, (GLenum) usage);
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
                CB_WARN("IBO copied");
            }
            return *this;
        }

        IBO& IBO::operator=(IBO&& other) noexcept {
            if (this != &other) {
                this->usage = other.usage;
                this->indexCount = other.indexCount;
                this->buffer = other.buffer;
                other.buffer = 0;
                CB_WARN("IBO moved");
            }
            return *this;
        }

        void IBO::bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        }

        void IBO::unbind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IBO IBO::fromQuads(const GLUsage usage, const uint count) {
            IBO ibo(usage, count * 6);
            ibo.bind();
            uint pattern[6] = {0, 1, 2, 2, 3, 0};
            uint indices[count * 6];
            for (int i = 0; i < count * 6; i++) {
                indices[i] = pattern[i % 6] + (i / 6) * 4;
            }
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * 6 * sizeof(uint), indices, (GLenum) usage);
            return ibo;
        }

        const uint IBO::getCount() const {
            return this->indexCount;
        }
    }
}