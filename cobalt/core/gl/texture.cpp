//
// Created by tomas on 01-12-2023.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "core/pch.h"
#include "core/gl/texture.h"


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

        static GLTextureEncoding getColorGLTextureEncoding(const uint channels, const bool isSrgb, const bool isHdr) {
            switch (channels) {
                case 1:
                    return isHdr ? GLTextureEncoding::RED_HDR : GLTextureEncoding::RED;
                case 2:
                    return isHdr ? GLTextureEncoding::RG_HDR : GLTextureEncoding::RG;
                case 3:
                    if (isSrgb) {
                        return GLTextureEncoding::SRGB;
                    } else {
                        return isHdr ? GLTextureEncoding::RGB_HDR : GLTextureEncoding::RGB;
                    }
                case 4:
                    if (isSrgb) {
                        return GLTextureEncoding::SRGBA;
                    } else {
                        return isHdr ? GLTextureEncoding::RGBA_HDR : GLTextureEncoding::RGBA;
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
            const bool isSrgb,
            const bool isHdr) {
            if (isColor) {
                return getColorGLTextureEncoding(channels, isSrgb, isHdr);
            } else if (isDepth) {
                if (isStencil) {
                    return GLTextureEncoding::DEPTH_STENCIL;
                } else {
                    return GLTextureEncoding::DEPTH;
                }
            }
            throw GLException("Invalid texture encoding");
        }

        Texture::Texture(const GLTextureFormat format, 
                         const GLTextureEncoding encoding) :
                         texture(0), format(format), encoding(encoding) {}

        Texture::~Texture() {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
        }

        Texture::Texture(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = std::move(other.source);
            other.texture = 0;
        }

        Texture& Texture::operator=(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = std::move(other.source);
            other.texture = 0;
            return *this;
        }
        
        Texture2D::Texture2D(const uchar red,
                             const uchar green,
                             const uchar blue,
                             const uchar alpha,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA) {
            source = "";
            GLubyte data[] = { red, green, blue, alpha };
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, 1, 1, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created 1x1 px 2D texture (GL: {0}) with encoding: {1}, format: {2}", texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const Color& color,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA) {
            source = "";
            GLubyte data[] = { (uchar) (color.r * 255.0f),
                               (uchar) (color.g * 255.0f),
                               (uchar) (color.b * 255.0f),
                               (uchar) (color.a * 255.0f) };
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, 1, 1, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created 1x1 px 2D texture (GL: {0}) with encoding: {1}, format: {2}", texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const uint width, const uint height, 
                             const GLTextureFormat format, 
                             const GLTextureEncoding encoding,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(format, encoding) {
            source = "";
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px 2D texture (GL: {2}) with encoding: {3}, format: {4}", width, height, texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const Path& path,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap,
                             const bool isSrgb) : 
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA){
            source = path.getFileName();
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            uchar* data = stbi_load(path.getPath().c_str(), &width, &height, &channels, 0);
            if (!data) {
                throw GLException("Failed to load texture: " + source);
            }
            format = getColorGLTextureFormat(channels);
            encoding = getColorGLTextureEncoding(channels, isSrgb, false);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, width, height, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            setFilter(filter);
            setWrap(wrap);
            stbi_image_free(data);
            CB_CORE_INFO("Loaded {0}x{1} px 2D texture (GL: {2}) from {3} with encoding: {4}, format: {4}", width, height, texture, path.getFileName(), getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        void Texture2D::reserve(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) encoding, this->width, this->height, 0, (GLenum) format, GL_UNSIGNED_BYTE, nullptr);
            CB_CORE_INFO("Reserved {0}x{1} px for texture (GL: {2})", this->width, this->height, texture);
        }

        void Texture2D::bind() const {
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture2D::bindToUnit(GLuint unit) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture2D::setWrap(GLTextureWrap wrap) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) wrap);
        }

        void Texture2D::setFilter(GLTextureFilter filter) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) filter);
        }

        Texture3D::Texture3D(const uchar red,
                             const uchar green,
                             const uchar blue,
                             const uchar alpha,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA) {
            source = "";
            GLubyte data[] = { red, green, blue, alpha };
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            for (uint i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint) encoding, 1, 1, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            }
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created 1x1 px per face cubemap (GL: {0}) with encoding: {1}, format: {2}", texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const Color& color,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA) {
            source = "";
            GLubyte data[] = { (uchar) (color.r * 255.0f),
                               (uchar) (color.g * 255.0f),
                               (uchar) (color.b * 255.0f),
                               (uchar) (color.a * 255.0f) };
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            for (uint i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint) encoding, 1, 1, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            }
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created 1x1 px per face cubemap (GL: {0}) with encoding: {1}, format: {2}", texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const uint width, const uint height, 
                             const GLTextureFormat format, 
                             const GLTextureEncoding encoding,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap) :
                             Texture(format, encoding) {
            source = "";
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px texture (GL: {2}) with encoding: {3}, format: {4}", width, height, texture, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const Path& path,
                             const GLTextureFilter filter,
                             const GLTextureWrap wrap,
                             const bool isSrgb) : 
                             Texture(GLTextureFormat::RGBA, GLTextureEncoding::RGBA){
            source = path.getFileName();
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            std::string faces[6] = {
                "right.png",
                "left.png",
                "bottom.png",
                "top.png",
                "front.png",
                "back.png"
            };
            for (uint i = 0; i < 6; i++) {
                uchar* data = stbi_load((path + faces[i]).getPath().c_str(), &width, &height, &channels, 0);
                if (!data) {
                    throw GLException("Failed to load texture: " + source);
                }
                format = getColorGLTextureFormat(channels);
                encoding = getColorGLTextureEncoding(channels, isSrgb, false);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint) encoding, width, height, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            CB_CORE_INFO("Loaded {0}x{1} px per face cubemap (GL: {2}) from {3} with encoding: {4}, format: {4}", width, height, texture, path.getFileName(), getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(filter), getGLTextureWrapName(wrap));
            setFilter(filter);
            setWrap(wrap);
        }

        void Texture3D::reserve(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            for (uint i = 0; i < 6; i++) {
                glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint) encoding, this->width, this->height, 0, (GLenum) format, GL_UNSIGNED_BYTE, nullptr);
            }
            CB_CORE_INFO("Reserved {0}x{1} px per face for cubemap (GL: {2})", this->width, this->height, texture);
        }

        void Texture3D::bind() const {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        }

        void Texture3D::bindToUnit(GLuint unit) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        }

        void Texture3D::setWrap(GLTextureWrap wrap) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLint) wrap);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLint) wrap);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLint) wrap);
        }

        void Texture3D::setFilter(GLTextureFilter filter) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLint) filter);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLint) filter);
        }

        TextureBuilder::TextureBuilder() : 
            width(1), height(1), 
            wrap(GLTextureWrap::Repeat), 
            filter(GLTextureFilter::Linear), 
            channels(4), 
            isColor(false), 
            isDepth(false), 
            isStencil(false), 
            isSrgb(false),
            isHdr(true) {}

        Texture2D TextureBuilder::buildEmpty2D() const {
            GLTextureFormat format = getGLTextureFormat(channels, isColor, isDepth, isStencil);
            GLTextureEncoding encoding = getGLTextureEncoding(channels, isColor, isDepth, isStencil, isSrgb, isHdr);
            return Texture2D(width, height, format, encoding, filter, wrap);
        }

        Texture2D TextureBuilder::buildFromSource2D(const Path& path) const {
            return Texture2D(path, filter, wrap, isSrgb);
        }

        Texture3D TextureBuilder::buildEmpty3D() const {
            GLTextureFormat format = getGLTextureFormat(channels, isColor, isDepth, isStencil);
            GLTextureEncoding encoding = getGLTextureEncoding(channels, isColor, isDepth, isStencil, isSrgb, isHdr);
            return Texture3D(width, height, format, encoding, filter, wrap);
        }

        Texture3D TextureBuilder::buildFromSource3D(const Path& path) const {
            return Texture3D(path, filter, wrap, isSrgb);
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

        TextureBuilder& TextureBuilder::setIsHdr(const bool isHdr) {
            this->isHdr = isHdr;
            return *this;
        }
    }
}