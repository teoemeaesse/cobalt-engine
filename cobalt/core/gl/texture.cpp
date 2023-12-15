//
// Created by tomas on 01-12-2023.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "core/gl/texture.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        static GLTextureFormat getColorGLTextureFormat(const uint channels) {
            switch (channels) {
                case 1:
                    return GLTextureFormat::RED;
                case 2:
                    return GLTextureFormat::RG;
                case 3:
                    return GLTextureFormat::RGB;
                case 4:
                    return GLTextureFormat::RGBA;
                default:
                    throw GLException("Invalid number of channels");
            }
        }

        static GLTextureEncoding getColorGLTextureEncoding(const uint channels, const bool isSrgb) {
            switch (channels) {
                case 1:
                    return GLTextureEncoding::RED;
                case 2:
                    return GLTextureEncoding::RG;
                case 3:
                    if (isSrgb) {
                        return GLTextureEncoding::SRGB;
                    } else {
                        return GLTextureEncoding::RGB;
                    }
                case 4:
                    if (isSrgb) {
                        return GLTextureEncoding::SRGBA;
                    } else {
                        return GLTextureEncoding::RGBA;
                    }
                default:
                    throw GLException("Invalid number of channels");
            }
        }

        static GLTextureFormat getGLTextureFormat(
            const uint channels,
            const bool isColor,
            const bool isDepth,
            const bool isStencil) {
            if (isColor) {
                return getColorGLTextureFormat(channels);
            } else if (isDepth) {
                if (isStencil) {
                    return GLTextureFormat::DEPTH_STENCIL;
                } else {
                    return GLTextureFormat::DEPTH;
                }
            }
            throw GLException("Invalid texture format");
        }

        static GLTextureEncoding getGLTextureEncoding(
            const uint channels,
            const bool isColor,
            const bool isDepth,
            const bool isStencil,
            const bool isSrgb) {
            if (isColor) {
                return getColorGLTextureEncoding(channels, isSrgb);
            } else if (isDepth) {
                if (isStencil) {
                    return GLTextureEncoding::DEPTH_STENCIL;
                } else {
                    return GLTextureEncoding::DEPTH;
                }
            }
            throw GLException("Invalid texture encoding");
        }

        Texture::Texture(const uint width, const uint height, 
                         const GLTextureFormat format, 
                         const GLTextureEncoding encoding,
                         const GLTextureFilter filter,
                         const GLTextureWrap wrap) : 
                         source(""), format(format), encoding(encoding) {
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px texture (GL: {2}) with encoding: {3}, format: {4}", width, height, texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture::Texture(const Path& path,
                         const GLTextureFilter filter,
                         const GLTextureWrap wrap,
                         const bool isSrgb) : 
                         source(path.getFileName()),
                         format(GLTextureFormat::RGBA),
                         encoding(GLTextureEncoding::RGBA) {
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            data = stbi_load(path.getPath().c_str(), &width, &height, &channels, 0);
            if (!data) {
                throw GLException("Failed to load texture: " + source);
            }
            format = getColorGLTextureFormat(channels);
            encoding = getColorGLTextureEncoding(channels, isSrgb);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, width, height, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Loaded {0}x{1} px texture (GL: {2}) from {3} with encoding: {4}, format: {4}", width, height, texture, path.getFileName(), getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture::~Texture() {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
                if (!source.empty()) {
                    stbi_image_free(data);
                }
            }
        }

        Texture::Texture(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = std::move(other.source);
            data = other.data;
            other.texture = 0;
        }

        Texture& Texture::operator=(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = std::move(other.source);
            data = other.data;
            other.texture = 0;
            return *this;
        }

        void Texture::reserve(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, this->width, this->height, 0, (GLenum) format, GL_UNSIGNED_BYTE, nullptr);
            CB_CORE_INFO("Reserved {0}x{1} px for texture (GL handle: {2})", this->width, this->height, texture);
        }

        void Texture::bind() const {
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture::bindToUnit(GLuint unit) const {
            glBindTextureUnit(unit, texture);
        }

        void Texture::setWrap(GLTextureWrap wrap) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) wrap);
        }

        void Texture::setFilter(GLTextureFilter filter) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) filter);
        }

        TextureBuilder::TextureBuilder() : 
            width(1), height(1), 
            wrap(GLTextureWrap::Repeat), 
            filter(GLTextureFilter::Linear), 
            channels(4), 
            isColor(false), 
            isDepth(false), 
            isStencil(false), 
            isSrgb(false) {}

        Texture TextureBuilder::buildEmpty() const {
            GLTextureFormat format = getGLTextureFormat(channels, isColor, isDepth, isStencil);
            GLTextureEncoding encoding = getGLTextureEncoding(channels, isColor, isDepth, isStencil, isSrgb);
            return Texture(width, height, format, encoding, filter, wrap);
        }

        Texture TextureBuilder::buildFromSource(const Path& path) const {
            return Texture(path, filter, wrap, isSrgb);
        }

        TextureBuilder& TextureBuilder::setDimensions(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            return *this;
        }

        TextureBuilder& TextureBuilder::setWrap(const GLTextureWrap wrap) {
            this->wrap = wrap;
            return *this;
        }

        TextureBuilder& TextureBuilder::setFilter(const GLTextureFilter filter) {
            this->filter = filter;
            return *this;
        }

        TextureBuilder& TextureBuilder::setChannels(const uint channels) {
            this->channels = channels;
            return *this;
        }

        TextureBuilder& TextureBuilder::setIsColor(const bool isColor) {
            this->isColor = isColor;
            return *this;
        }

        TextureBuilder& TextureBuilder::setIsDepth(const bool isDepth) {
            this->isDepth = isDepth;
            return *this;
        }

        TextureBuilder& TextureBuilder::setIsStencil(const bool isStencil) {
            this->isStencil = isStencil;
            return *this;
        }

        TextureBuilder& TextureBuilder::setIsSrgb(const bool isSrgb) {
            this->isSrgb = isSrgb;
            return *this;
        }
    }
}