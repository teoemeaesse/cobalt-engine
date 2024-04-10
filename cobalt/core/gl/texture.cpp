// Created by tomas on
// 01-12-2023

#ifdef TEST_ENVIRONMENT
#define STBI_NO_SIMD
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "core/gl/texture.h"

#include "core/gl/exception.h"
#include "stb_image/stb_image.h"

namespace cobalt {
    namespace core::gl {
        Texture::Texture(const gl::TextureEncoding encoding)
            : texture(0), format(gl::getTextureFormat(encoding)), encoding(encoding), pixelType(gl::getPixelType(encoding)) {}

        Texture::Texture(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = Move(other.source);
            other.texture = 0;
        }

        Texture& Texture::operator=(Texture&& other) noexcept {
            texture = other.texture;
            width = other.width;
            height = other.height;
            format = other.format;
            encoding = other.encoding;
            source = Move(other.source);
            other.texture = 0;
            return *this;
        }

        Texture2D::Texture2D(const Color& color, const gl::TextureEncoding encoding, const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = 1;
            this->height = 1;
            uchar data[4];
            color.toUChar(data);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint)encoding, 1, 1, 0, (GLenum)format, (GLenum)pixelType, data);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px 2D texture (GL: {2}) with encoding: {3}, format: {4}, pixels: {5}", width, height, texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const void* data, const gl::TextureEncoding encoding, const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = 1;
            this->height = 1;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint)encoding, 1, 1, 0, (GLenum)format, (GLenum)pixelType, data);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created 1x1 px 2D texture (GL: {0}) with encoding: {1}, format: {2}, pixels: {3}", texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const uint width, const uint height, const gl::TextureEncoding encoding, const gl::TextureFilter filter,
                             const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = width;
            this->height = height;
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px 2D texture (GL: {2}) with encoding: {3}, format: {4}", width, height, texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture2D::Texture2D(const io::Path& path, const bool srgb, const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(srgb ? gl::TextureEncodings::SRGBA::Bits8 : gl::TextureEncodings::RGBA::Bits8) {
            // STBI only supports 8-bit images, and doesn't really give much metadata about the image, so we'll just assume it's 8-bit for now
            // TODO: switch loader library (roll custom?)
            source = path.getFileName();
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            uchar* data = stbi_load(path.getPath().c_str(), &width, &height, &channels, STBI_rgb_alpha);
            if (!data) {
                throw GLException("Failed to load texture: " + source);
            }
            this->width = width;
            this->height = height;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint)encoding, width, height, 0, (GLenum)format, (GLenum)pixelType, data);
            setFilter(filter);
            setWrap(wrap);
            stbi_image_free(data);
            CB_CORE_INFO("Loaded {0}x{1} px 2D texture (GL: {2}) from {3} with encoding: {4}, format: {4}", width, height, texture,
                         path.getFileName(), gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture2D::~Texture2D() {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
        }

        Texture2D::Texture2D(Texture2D&& other) noexcept : Texture(Move(other)) {}

        Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
            Texture::operator=(Move(other));
            return *this;
        }

        void Texture2D::reserve(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint)encoding, this->width, this->height, 0, (GLenum)format, (GLenum)pixelType, nullptr);
        }

        void Texture2D::bind() const { glBindTexture(GL_TEXTURE_2D, texture); }

        void Texture2D::bindToUnit(GLuint unit) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        void Texture2D::setWrap(gl::TextureWrap wrap) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap);
        }

        void Texture2D::setFilter(gl::TextureFilter filter) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)filter);
        }

        Texture3D::Texture3D(const uchar red, const uchar green, const uchar blue, const uchar alpha, const gl::TextureEncoding encoding,
                             const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = 1;
            this->height = 1;
            GLubyte data[] = {red, green, blue, alpha};
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            for (uint i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint)encoding, 1, 1, 0, (GLenum)format, (GLenum)pixelType, data);
            }
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px/face cubemap (GL: {2}) with encoding: {3}, format: {4}, pixels: {5}", width, height, texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const Color& color, const gl::TextureEncoding encoding, const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = 1;
            this->height = 1;
            uchar data[4];
            color.toUChar(data);
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            for (uint i = 0; i < 6; i++) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint)encoding, 1, 1, 0, (GLenum)format, (GLenum)pixelType, data);
            }
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px/face 3D texture (GL: {2}) with encoding: {3}, format: {4}, pixels: {5}", width, height, texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const uint width, const uint height, const gl::TextureEncoding encoding, const gl::TextureFilter filter,
                             const gl::TextureWrap wrap)
            : Texture(encoding) {
            source = "";
            this->width = width;
            this->height = height;
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(filter);
            setWrap(wrap);
            CB_CORE_INFO("Created {0}x{1} px texture (GL: {2}) with encoding: {3}, format: {4}", width, height, texture,
                         gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
        }

        Texture3D::Texture3D(const io::Path& path, const bool srgb, const gl::TextureFilter filter, const gl::TextureWrap wrap)
            : Texture(srgb ? gl::TextureEncodings::SRGBA::Bits8 : gl::TextureEncodings::RGBA::Bits8) {
            // STBI only supports 8-bit images, and doesn't really give much metadata about the image, so we'll just assume it's 8-bit for now
            // TODO: switch loader library (roll custom?)
            source = path.getFileName();
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            std::string faces[6] = {"right.png", "left.png", "bottom.png", "top.png", "front.png", "back.png"};
            for (uint i = 0; i < 6; i++) {
                uchar* data = stbi_load((path + faces[i]).getPath().c_str(), &width, &height, &channels, STBI_rgb_alpha);
                if (!data) {
                    throw GLException("Failed to load texture: " + source);
                }
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint)encoding, width, height, 0, (GLenum)format, (GLenum)pixelType, data);
                stbi_image_free(data);
            }
            this->width = width;
            this->height = height;
            CB_CORE_INFO("Loaded {0}x{1} px/face 3D texture (GL: {2}) from {3} with encoding: {4}, format: {4}", width, height, texture,
                         path.getFileName(), gl::getTextureEncodingName(encoding), gl::getTextureFormatName(format), gl::getPixelTypeName(pixelType));
            CB_CORE_INFO("Using filter: {0}, wrap: {1}", gl::getTextureFilterName(filter), gl::getTextureWrapName(wrap));
            setFilter(filter);
            setWrap(wrap);
        }

        Texture3D::~Texture3D() {
            if (texture != 0) {
                glDeleteTextures(1, &texture);
            }
        }

        Texture3D::Texture3D(Texture3D&& other) noexcept : Texture(Move(other)) {}

        Texture3D& Texture3D::operator=(Texture3D&& other) noexcept {
            Texture::operator=(Move(other));
            return *this;
        }

        void Texture3D::reserve(const uint width, const uint height) {
            this->width = width;
            this->height = height;
            for (uint i = 0; i < 6; i++) {
                glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (GLint)encoding, this->width, this->height, 0, (GLenum)format, (GLenum)pixelType,
                             nullptr);
            }
        }

        void Texture3D::bind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, texture); }

        void Texture3D::bindToUnit(const GLuint unit) const {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        }

        void Texture3D::setWrap(const gl::TextureWrap wrap) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLint)wrap);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLint)wrap);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLint)wrap);
        }

        void Texture3D::setFilter(const gl::TextureFilter filter) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLint)filter);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLint)filter);
        }
    }  // namespace core::gl
}  // namespace cobalt