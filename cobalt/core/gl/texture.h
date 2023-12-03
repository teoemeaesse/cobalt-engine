//
// Created by tomas on 01-12-2023.
//

#pragma once

#include "core/containers/types.h"
#include "core/gl/definitions.h"
#include "core/io/path.h"


namespace cobalt {
    namespace core {
        class Texture {
            public:
            /* Creates an empty texture with the given width and height
             * and reserves the memory for it.
             * The format is the internal format of the texture.
             * @param width: The width of the texture.
             * @param height: The height of the texture.
             * @param format: The pixel format of the texture.
             * @param encoding: The internal format of the texture.
             * @return: The created texture.
             */
            Texture(const uint width, const uint height,
                    const GLTextureFormat format = GLTextureFormat::RGBA,
                    const GLTextureEncoding encoding = GLTextureEncoding::RGBA8);
            /* Creates a texture from the given path.
             * The format is the internal format of the texture.
             * @param path: The path to the texture.
             * @param format: The pixel format of the texture.
             * @param encoding: The internal format of the texture.
             * @return: The created texture.
             */
            Texture(const Path& path,
                    const GLTextureFormat format = GLTextureFormat::RGBA,
                    const GLTextureEncoding encoding = GLTextureEncoding::RGBA8);
            /* Destroys the texture and frees the memory.
             */
            ~Texture();

            /* Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height);
            /* Binds the texture to the current opengl rendering context.
             */
            void bind() const;
            /* Binds the texture to the given texture unit.
             * @param unit: The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const;
            /* Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            void setWrap(const GLTextureWrap wrap);
            /* Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            void setFilter(const GLTextureFilter filter);

            /* Returns the GL handle to the texture.
             * @return: The GL handle to the texture.
             */
            inline GLHandle getGLHandle() const { return texture; }
            /* Returns the width of the texture.
             * @return: The width of the texture.
             */
            inline uint getWidth() const { return width; }
            /* Returns the height of the texture.
             * @return: The height of the texture.
             */
            inline uint getHeight() const { return height; }
            /* Returns the pixel encoding of the texture.
             * @return: The pixel encoding of the texture.
             */
            inline GLTextureEncoding getEncoding() const { return encoding; }

            private:
            GLHandle texture;                   // The OpenGL handle to the texture.
            const std::string source;           // The source of the texture.
            const GLTextureFormat format;       // The pixel format of the texture.
            const GLTextureEncoding encoding;   // The internal format of the texture.
            uint width, height;                 // The width and height of the texture.
            uchar *data;                        // The raw data of the texture.
        };
    }
}