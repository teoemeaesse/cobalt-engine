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
        Texture::Texture(uint width, uint height, GLTextureFormat format) : source(""), format(format), width(width), height(height) {
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(DEFAULT_TEXTURE_FILTER);
            setWrap(DEFAULT_TEXTURE_WRAP);
            CB_CORE_INFO("Created {0}x{1} px texture with format: {2}", width, height, getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(DEFAULT_TEXTURE_FILTER), getGLTextureWrapName(DEFAULT_TEXTURE_WRAP));
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        Texture::Texture(Path& path, GLTextureFormat format) : source(path.getFileName()), format(format) {
            int width, height, channels;
            stbi_set_flip_vertically_on_load(true);
            data = stbi_load(path.getPath().c_str(), &width, &height, &channels, 0);
            if (!data) {
                throw GLException("Failed to load texture: " + source);
            }
            this->width = width;
            this->height = height;
            glGenTextures(1, &texture);
            reserve(width, height);
            setFilter(DEFAULT_TEXTURE_FILTER);
            setWrap(DEFAULT_TEXTURE_WRAP); 
            CB_CORE_INFO("Loaded {0}x{1} px texture from {2} with format: {3}", width, height, path.getFileName(), getGLTextureFormatName(format));
            CB_CORE_INFO("Using default filter: {0}, wrap: {1}", getGLTextureFilterName(DEFAULT_TEXTURE_FILTER), getGLTextureWrapName(DEFAULT_TEXTURE_WRAP));
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        Texture::~Texture() {
            glDeleteTextures(1, &texture);
            if (source.empty()) {
                stbi_image_free(data);
            }
        }

        void Texture::reserve(uint width, uint height) {
            if (width * height == 0) {
                width = this->width;
                height = this->height;
            }
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, (GLint) format, width, height, 0, (GLenum) format, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void Texture::bind() {
            glBindTexture(GL_TEXTURE_2D, texture);   
        }

        void Texture::bindToUnit(GLuint unit) {
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