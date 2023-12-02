//
// Created by tomas on 02-12-2023.
//

#include "core/gl/fbo.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        FBO::FBO(const uint width, const uint height, const GLFramebufferAttachment type = GLFramebufferAttachment::Color, const GLTextureFormat format = GLTextureFormat::RGBA) : texture(width, height, format), type(type) {
            glGenFramebuffers(1, &buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
            texture.bind();
            glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum) type, GL_TEXTURE_2D, texture.getGLHandle(), 0);
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                throw GLException("Failed to create FBO");
            }
            CB_CORE_INFO("Created a {0}x{1} px FBO", width, height);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        FBO::FBO(const uint width, const uint height) : 
            buffer(0),
            texture(width, height, GLTextureFormat::RGBA),
            type((GLFramebufferAttachment) 0) {
        }

        FBO::~FBO() {
            if (buffer != 0) {
                glDeleteFramebuffers(1, &buffer);
            }
        }

        void FBO::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
        }

        void FBO::unbind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void FBO::resize(const uint width, const uint height) {
            texture.reserve(width, height);
        }

        void FBO::clear() {
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            switch (type) {
                case GLFramebufferAttachment::Color:
                    glClear(GL_COLOR_BUFFER_BIT);
                    break;
                case GLFramebufferAttachment::Depth:
                    glClear(GL_DEPTH_BUFFER_BIT);
                    break;
                case GLFramebufferAttachment::Stencil:
                    glClear(GL_STENCIL_BUFFER_BIT);
                    break;
            }
        }
    }
}