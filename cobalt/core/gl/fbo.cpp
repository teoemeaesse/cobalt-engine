//
// Created by tomas on 02-12-2023.
//

#include "core/gl/fbo.h"
#include "core/pch.h"


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

        const uint FBO::getWidth() const {
            return width;
        }

        const uint FBO::getHeight() const {
            return height;
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

        TargetFBO::TargetFBO(const uint width, const uint height, 
                             const GLFramebufferAttachment type,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap,
                             const bool srgb) : FBO(type) {
            glGenFramebuffers(1, &buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Color)) {\
                TextureBuilder builder = TextureBuilder().setDimensions(width, height)
                                                         .setFilter(filter)
                                                         .setWrap(wrap)
                                                         .setIsSrgb(srgb)
                                                         .setIsHdr(true);
                color = builder.setChannels(4).setIsColor(true).buildEmpty2D();
                color.value().bind();
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color.value().getGLHandle(), 0);
            }
            if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Depth)) {
                TextureBuilder builder = TextureBuilder().setDimensions(width, height)
                                                         .setFilter(filter)
                                                         .setWrap(wrap)
                                                         .setIsSrgb(srgb)
                                                         .setIsHdr(false);
                builder.setIsDepth(true);
                if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Stencil)) {
                    builder.setIsStencil(true);
                }
                depthStencil = builder.buildEmpty2D();
                depthStencil.value().bind();
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthStencil.value().getGLHandle(), 0);
                if (static_cast<int>(type) & static_cast<int>(GLFramebufferAttachment::Stencil)) {
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencil.value().getGLHandle(), 0);
                }
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
            this->width = width;
            this->height = height;
            if (color.has_value()) color.value().reserve(width, height);
            if (depthStencil.has_value()) depthStencil.value().reserve(width, height);
            CB_CORE_INFO("Resized FBO to {0}x{1} px (GL: {2})", width, height, buffer);
        }

        void TargetFBO::bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
        }

        const bool TargetFBO::hasAttachment(const GLFramebufferAttachment attachment) const {
            return static_cast<int>(type) & static_cast<int>(attachment);
        }

        const Texture& TargetFBO::getColorBuffer() const {
            if (!hasAttachment(GLFramebufferAttachment::Color)) {
                throw GLException("FBO does not have a color buffer attachment");
            }
            return color.value();
        }

        const Texture& TargetFBO::getDepthBuffer() const {
            if (!hasAttachment(GLFramebufferAttachment::Depth)) {
                throw GLException("FBO does not have a depth buffer attachment");
            }
            return depthStencil.value();
        }
        
        const Texture& TargetFBO::getStencilBuffer() const {
            if (!hasAttachment(GLFramebufferAttachment::Stencil)) {
                throw GLException("FBO does not have a stencil buffer attachment");
            }
            return depthStencil.value();
        }
    }
}