//
// Created by tomas on 01-12-2023.
//

#pragma once

#include "core/utils/types.h"
#include "core/gl/definitions.h"
#include "core/io/path.h"


namespace cobalt {
    namespace core {
        class Texture {
            public:
            /* Destroys the texture and frees the memory.
             */
            ~Texture();
            /* Copy constructor.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture(const Texture& other) = delete;
            /* Move constructor.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture(Texture&& other) noexcept;
            /* Copy assignment operator.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture& operator=(const Texture& other) = delete;
            /* Move assignment operator.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture& operator=(Texture&& other) noexcept;

            /* Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            virtual void reserve(const uint width, const uint height) = 0;
            /* Binds the texture to the current opengl rendering context.
             */
            virtual void bind() const = 0;
            /* Binds the texture to the given texture unit.
             * @param unit: The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const;
            /* Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            virtual void setWrap(const GLTextureWrap wrap) = 0;
            /* Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            virtual void setFilter(const GLTextureFilter filter) = 0;

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

            protected:
            GLHandle texture;                   // The OpenGL handle to the texture.
            std::string source;                 // The source of the texture.
            GLTextureFormat format;             // The pixel format of the texture.
            GLTextureEncoding encoding;         // The internal format of the texture.
            uint width, height;                 // The width and height of the texture.

            /* Creates an opengl texture.
             * @param texture: The OpenGL handle to the texture.
             * @param format: The pixel format of the texture.
             * @param encoding: The internal format of the texture.
             * @return: The created texture.
             */
            Texture(const GLTextureFormat format,
                    const GLTextureEncoding encoding);
        };

        class Texture2D : public Texture {
            friend class TextureBuilder;

            /* Creates an empty 2d texture with the given width and height
             * and reserves the memory for it.
             * @param width: The width of the texture.
             * @param height: The height of the texture.
             * @param format: The pixel format of the texture.
             * @param encoding: The internal format of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture2D(const uint width, const uint height,
                      const GLTextureFormat format = GLTextureFormat::RGBA,
                      const GLTextureEncoding encoding = GLTextureEncoding::RGBA,
                      const GLTextureFilter filter = GLTextureFilter::Linear,
                      const GLTextureWrap wrap = GLTextureWrap::Repeat);
            /* Creates a 2d texture from the given path to a file.
             * @param path: The path to the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @param isSrgb: Whether the texture is in srgb color space.
             * @return: The created texture.
             */
            Texture2D(const Path& path,
                      const GLTextureFilter filter = GLTextureFilter::Linear,
                      const GLTextureWrap wrap = GLTextureWrap::Repeat,
                      const bool isSrgb = false);
            
            /* Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /* Binds the texture to the current opengl rendering context.
             */
            void bind() const override;
            /* Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            void setWrap(const GLTextureWrap wrap) override;
            /* Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            void setFilter(const GLTextureFilter filter) override;
        };

        class Texture3D : public Texture {
            friend class TextureBuilder;

            /* Creates an empty cubemap with the given width and height 
             * for the faces and reserves the memory for it.
             * The format is the internal format of the texture.
             * @param width: The width of the texture.
             * @param height: The height of the texture.
             * @param format: The pixel format of the texture.
             * @param encoding: The internal format of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture3D(const uint width, const uint height,
                      const GLTextureFormat format = GLTextureFormat::RGBA,
                      const GLTextureEncoding encoding = GLTextureEncoding::RGBA,
                      const GLTextureFilter filter = GLTextureFilter::Linear,
                      const GLTextureWrap wrap = GLTextureWrap::Repeat);
            /* Creates a cubemap from the given path to a directory containing the faces
             * in 6 distinct png files: right.png, left.png, top.png, bottom.png, front.png, back.png.
             * @param path: The path to the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @param isSrgb: Whether the texture is in srgb color space.
             * @return: The created texture.
             */
            Texture3D(const Path& path,
                      const GLTextureFilter filter = GLTextureFilter::Linear,
                      const GLTextureWrap wrap = GLTextureWrap::Repeat,
                      const bool isSrgb = false);
            
            /* Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /* Binds the texture to the current opengl rendering context.
             */
            void bind() const override;
            /* Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            void setWrap(const GLTextureWrap wrap) override;
            /* Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            void setFilter(const GLTextureFilter filter) override;
        };

        class TextureBuilder {
            public:
            /* Constructs a TextureBuilder object with the default configuration.
             * @return: The constructed TextureBuilder object.
             */
            TextureBuilder();
            /* Destroys the TextureBuilder object.
             */
            ~TextureBuilder() = default;

            /* Constructs an empty Texture2D object based on the current configuration.
             * @return: The constructed Texture2D object.
             */
            Texture2D buildEmpty2D() const;
            /* Constructs a Texture2D object from a source based on the current configuration.
             * @return: The constructed Texture2D object.
             */
            Texture2D buildFromSource2D(const Path& path) const;

            /* Constructs an empty Texture3D object based on the current configuration.
             * @return: The constructed Texture2D object.
             */
            Texture3D buildEmpty3D() const;
            /* Constructs a Texture3D object from a source based on the current configuration.
             * @return: The constructed Texture3D object.
             */
            Texture3D buildFromSource3D(const Path& path) const;

            /* Sets the dimensions of the texture.
             * @param width: The width of the texture in pixels.
             * @param height: The height of the texture in pixels.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setDimensions(const uint width, const uint height);
            /* Sets the wrapping mode of the texture.
             * @param wrap: The GLTextureWrap enum specifying the wrap mode.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setWrap(const GLTextureWrap wrap);
            /* Sets the filtering mode of the texture.
             * @param filter: The GLTextureFilter enum specifying the filter mode.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setFilter(const GLTextureFilter filter);
            /* Sets the number of channels of the texture.
             * This is irrelevant if the texture is a depth or stencil buffer.
             * @param channels: The number of channels.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setChannels(const uint channels);
            /* Sets whether the texture is a color buffer.
             * Mutually exclusive with setIsDepth and setIsStencil.
             * @param isColor: Whether the texture is a color texture.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setIsColor(const bool isColor);
            /* Sets whether the texture is a depth buffer.
             * Mutually exclusive with setIsColor.
             * @param isDepth: Whether the texture is a depth texture.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setIsDepth(const bool isDepth);
            /* Sets whether the texture is a stencil buffer.
             * Mutually exclusive with setIsColor.
             * Assumes that the texture is a depth buffer as well.
             * @param isStencil: Whether the texture is a stencil texture.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setIsStencil(const bool isStencil);
            /* Sets whether the texture is in srgb color space.
             * @param isSrgb: Whether the texture is in srgb color space.
             * @return: Reference to the current TextureBuilder instance.
             */
            TextureBuilder& setIsSrgb(const bool isSrgb);

            private:
            uint channels;
            uint width, height;
            bool isColor;
            bool isDepth;
            bool isStencil;
            bool isSrgb;
            GLTextureWrap wrap;
            GLTextureFilter filter;
        };
    }
}