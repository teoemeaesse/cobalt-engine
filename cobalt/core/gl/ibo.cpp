//
// Created by tomas on 30-11-2023.
//

#include "core/gl/ibo.h"


namespace cobalt {
    namespace core {
        IBO::IBO(const GLUsage usage, const uint indexCount) : usage(usage), indexCount(indexCount) {
            glGenBuffers(1, &buffer);
        }

        IBO::~IBO() {
            glDeleteBuffers(1, &buffer);
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