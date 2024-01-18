//
// Created
// by
// tomas
// on
// 02-12-2023.
//

#include "core/gl/fbo.h"

#include "core/gfx/render_context.h"
#include "core/pch.h"

namespace cobalt {
    namespace core {
        FBO::FBO(const uint width, const uint height, const Vec<Attachment>& attachments) : width(width), height(height), clearColor(COLOR_BLACK) {
            glGenFramebuffers(1, &buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, buffer);
            for (auto& attachment : attachments) {
                GL::TextureFormat type = GL::getTextureFormat(attachment.encoding);
                switch (type) {
                    case GL::TextureFormats::Stencil:
                        stencil.emplace(width, height, attachment.encoding, attachment.filter, attachment.wrap);
                        stencil.value().bind();
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencil.value().getGLHandle(), 0);
                        break;
                    case GL::TextureFormats::Depth:
                        depth.emplace(width, height, attachment.encoding, attachment.filter, attachment.wrap);
                        depth.value().bind();
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth.value().getGLHandle(), 0);
                        break;
                    case GL::TextureFormats::DepthStencil:
                        depthStencil.emplace(width, height, attachment.encoding, attachment.filter, attachment.wrap);
                        depthStencil.value().bind();
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthStencil.value().getGLHandle(), 0);
                        break;
                    case GL::TextureFormats::R:
                    case GL::TextureFormats::RG:
                    case GL::TextureFormats::RGB:
                    case GL::TextureFormats::RGBA: {
                        const uint maxColorAttachments = RenderContext::queryMaxColorAttachments();
                        if (colors.size() > maxColorAttachments) {
                            CB_CORE_WARN("Attempting to add more color attachments to FBO than the maximum supported ({0}).", maxColorAttachments);
                        }
                        const uint id = colors.size();
                        colors.emplace_back(width, height, attachment.encoding, attachment.filter, attachment.wrap);
                        colors[id].bind();
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + id, GL_TEXTURE_2D, colors[id].getGLHandle(), 0);
                    }
                        continue;
                    case GL::TextureFormats::Unknown:
                    default:
                        CB_CORE_WARN("Attempting to add an unknown attachment type to FBO.");
                        break;
                }
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                    throw GLException("Failed to create FBO");
                }
                CB_CORE_INFO("Created a {0}x{1} px FBO", width, height);
            }
        }

        FBO::FBO() : buffer(0), clearColor(COLOR_GREEN) {
            int width, height;
            glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
            this->width = (uint)width;
            this->height = (uint)height;
        }

        FBO::FBO(FBO&& other) noexcept
            : buffer(other.buffer),
              width(other.width),
              height(other.height),
              clearColor(other.clearColor),
              colors(std::move(other.colors)),
              depth(std::move(other.depth)),
              stencil(std::move(other.stencil)),
              depthStencil(std::move(other.depthStencil)) {
            other.buffer = 0;
        }

        FBO& FBO::operator=(FBO&& other) noexcept {
            if (buffer != 0) {
                glDeleteFramebuffers(1, &buffer);
            }
            buffer = other.buffer;
            width = other.width;
            height = other.height;
            clearColor = other.clearColor;
            colors = std::move(other.colors);
            depth = std::move(other.depth);
            stencil = std::move(other.stencil);
            depthStencil = std::move(other.depthStencil);
            other.buffer = 0;
            return *this;
        }

        FBO::~FBO() {
            if (buffer != 0) {
                glDeleteFramebuffers(1, &buffer);
            }
        }

        void FBO::resize(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            if (buffer == 0) {
                glViewport(0, 0, width, height);
                CB_CORE_INFO("Resized default FBO to {0}x{1} px", width, height);
            } else {
                for (uint i = 0; i < colors.size(); i++) {
                    colors[i].reserve(width, height);
                }
                if (depth.has_value()) depth.value().reserve(width, height);
                if (stencil.has_value()) stencil.value().reserve(width, height);
                if (depthStencil.has_value()) depthStencil.value().reserve(width, height);
                CB_CORE_INFO("Resized FBO to {0}x{1} px (GL: {2})", width, height, buffer);
            }
        }

        void FBO::bind() const { glBindFramebuffer(GL_FRAMEBUFFER, buffer); }

        void FBO::clear() const {
            bind();
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            int mask = 0;
            if (!colors.empty()) {
                mask |= GL_COLOR_BUFFER_BIT;
            }
            if (depth.has_value() || depthStencil.has_value()) {
                mask |= GL_DEPTH_BUFFER_BIT;
            }
            if (stencil.has_value() || depthStencil.has_value()) {
                mask |= GL_STENCIL_BUFFER_BIT;
            }
            glClear(mask);
        }

        void FBO::setClearColor(const Color& color) { clearColor = color; }

        const Opt<Wrap<const Texture2D>> FBO::getColorBuffer(const uint i) const {
            if (i >= colors.size() || colors.empty()) {
                return None;
            }
            return createWrap(colors[i]);
        }

        const Opt<Wrap<const Texture2D>> FBO::getColorBuffer() const { return getColorBuffer(0); }

        const Opt<Wrap<const Texture2D>> FBO::getDepthBuffer() const {
            if (!depth.has_value()) {
                if (!depthStencil.has_value()) {
                    return None;
                }
                return createWrap(depthStencil.value());
            }
            return createWrap(depth.value());
        }

        const Opt<Wrap<const Texture2D>> FBO::getStencilBuffer() const {
            if (!stencil.has_value()) {
                if (!depthStencil.has_value()) {
                    return None;
                }
                return createWrap(depthStencil.value());
            }
            return createWrap(stencil.value());
        }

        const uint FBO::getWidth() const { return width; }

        const uint FBO::getHeight() const { return height; }
    }  // namespace core
}  // namespace cobalt