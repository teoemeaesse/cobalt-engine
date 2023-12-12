//
// Created by tomas on 01-12-2023.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "core/gl/texture.h"
#include "core/utils/log.h"


#define DEFAULT_TEXTURE_FILTER GLTextureFilter::Linear
#define DEFAULT_TEXTURE_WRAP GLTextureWrap::Repeat

namespace cobalt {
    namespace core {
        Texture::Texture(const uint width, const uint height, 
                         const GLTextureFormat format, 
                         const GLTextureEncoding encoding) : 
                         source(""), format(format), encoding(encoding) {
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(DEFAULT_TEXTURE_FILTER);
            setWrap(DEFAULT_TEXTURE_WRAP);
            glBindTexture(GL_TEXTURE_2D, 0);
            CB_CORE_INFO("Created {0}x{1} px texture with encoding: {2}, format: {3}", width, height, getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(DEFAULT_TEXTURE_FILTER), getGLTextureWrapName(DEFAULT_TEXTURE_WRAP));
        }

        Texture::Texture(const Path& path,
                         const GLTextureFormat format,
                         const GLTextureEncoding encoding) : 
                         source(path.getFileName()), format(format), encoding(encoding) {
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            data = stbi_load(path.getPath().c_str(), &width, &height, &channels, 0);
            if (!data) {
                throw GLException("Failed to load texture: " + source);
            }
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(DEFAULT_TEXTURE_FILTER);
            setWrap(DEFAULT_TEXTURE_WRAP); 
            glBindTexture(GL_TEXTURE_2D, 0);
            CB_CORE_INFO("Loaded {0}x{1} px texture from {2} with encoding: {3}, format: {4}", width, height, path.getFileName(), getGLTextureEncodingName(encoding), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(DEFAULT_TEXTURE_FILTER), getGLTextureWrapName(DEFAULT_TEXTURE_WRAP));
        }

        Texture::~Texture() {
            if (texture != 0) {
                CB_CORE_WARN("Destroyed texture (GL handle: {0})", texture);
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
            CB_CORE_WARN("Moved texture (GL handle: {0})", texture);
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
            CB_CORE_WARN("Moved texture (GL handle: {0})", texture);
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
            glBindTextureUnit(GL_TEXTURE0 + unit, texture);
        }

        void Texture::setWrap(GLTextureWrap wrap) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) wrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) wrap);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture::setFilter(GLTextureFilter filter) {
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) filter);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}