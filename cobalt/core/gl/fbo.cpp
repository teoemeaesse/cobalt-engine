//
// Created by tomas on 02-12-2023.
//

#include "core/gl/fbo.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        FBO::FBO(const GLFramebufferAttachment type)
            : type(type) {}
        
        void FBO::clear() const {
            bind();
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            int mask = 0;
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Color)) {
                mask |= GL_COLOR_BUFFER_BIT;
            }
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Depth)) {
                mask |= GL_DEPTH_BUFFER_BIT;
            }
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Stencil)) {
                mask |= GL_STENCIL_BUFFER_BIT;
            }
            glClear(mask);
        }

        void FBO::setClearColor(const Color& color) {
            clearColor = color;
        }

        DefaultFBO::DefaultFBO(const GLFramebufferAttachment type)
            : FBO(type) {
            int width, height;
            glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
            this->width = (uint) width;
            this->height = (uint) height;
        }

        void DefaultFBO::resize(const uint width, const uint height) {
            glViewport(0, 0, width, height);
            this->width = width;
            this->height = height;
        }

        void DefaultFBO::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        const uint DefaultFBO::getWidth() const {
            return width;
        }

        const uint DefaultFBO::getHeight() const {
            return height;
        }

        TargetFBO::TargetFBO(const uint width, const uint height, 
                             const GLFramebufferAttachment type,
                             const GLTextureFormat format,
                             const GLTextureEncoding encoding) : 
                             texture(width, height, format, encoding), FBO(type) {
            glGenFramebuffers(1, &buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
            texture.bind();
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Color)) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getGLHandle(), 0);
            }
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Depth)) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.getGLHandle(), 0);
            }
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Stencil)) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.getGLHandle(), 0);
            }
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                throw GLException("Failed to create FBO");
            }
            CB_CORE_INFO("Created a {0}x{1} px FBO", width, height);
        }

        TargetFBO::~TargetFBO() {
            glDeleteFramebuffers(1, &buffer);
        }

        void TargetFBO::resize(const uint width, const uint height) {
            texture.reserve(width, height);
            CB_CORE_INFO("Resized FBO to {2}x{3} px (GL handle: {0} - Tex GL handle: {1})", buffer, texture.getGLHandle(), width, height);
        }

        void TargetFBO::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
        }

        const Texture& TargetFBO::getTexture() const {
            return texture;
        }

        const uint TargetFBO::getWidth() const {
            return texture.getWidth();
        }

        const uint TargetFBO::getHeight() const {
            return texture.getHeight();
        }
    }
}