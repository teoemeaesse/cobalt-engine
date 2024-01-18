//
// Created
// by
// tomas
// on
// 01-12-2023.
//

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        class Texture {
            public:
            /** @brief: Destroys the texture and frees the memory.
             */
            ~Texture();
            /** @brief: Copy constructor.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture(const Texture& other) = delete;
            /** @brief: Move constructor.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture(Texture&& other) noexcept;
            /** @brief: Copy assignment operator.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture& operator=(const Texture& other) = delete;
            /** @brief: Move assignment operator.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture& operator=(Texture&& other) noexcept;

            /** @brief: Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            virtual void reserve(const uint width, const uint height) = 0;
            /** @brief: Binds the texture to the current OpenGL rendering context.
             */
            virtual void bind() const = 0;
            /** @brief: Binds the texture to the given texture unit.
             * @param unit: The texture unit to bind the texture to.
             */
            virtual void bindToUnit(const GLuint unit) const = 0;
            /** @brief: Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            virtual void setWrap(const gl::TextureWrap wrap) = 0;
            /** @brief: Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            virtual void setFilter(const gl::TextureFilter filter) = 0;

            /** @brief: Returns the GL handle to the texture.
             * @return: The GL handle to the texture.
             */
            inline gl::Handle getGLHandle() const { return texture; }
            /** @brief: Returns the width of the texture.
             * @return: The width of the texture.
             */
            inline uint getWidth() const { return width; }
            /** @brief: Returns the height of the texture.
             * @return: The height of the texture.
             */
            inline uint getHeight() const { return height; }
            /** @brief: Returns the pixel encoding of the texture.
             * @return: The pixel encoding of the texture.
             */
            inline gl::TextureEncoding getEncoding() const { return encoding; }

            protected:
            gl::Handle texture;            // The OpenGL handle to the texture.
            std::string source;            // The source of the texture.
            gl::TextureFormat format;      // The pixel format of the texture.
            gl::TextureEncoding encoding;  // The internal format of the texture.
            uint width, height;            // The width and height of the texture.

            /** @brief: Creates an OpenGL texture.
             * @param encoding: The internal format of the texture.
             * @return: The created texture.
             */
            Texture(const gl::TextureEncoding encoding);
        };

        class Texture2D : public Texture {
            public:
            /** @brief: Creates a 1x1 texture from the given color.
             * @param red: The red component of the color (0-255).
             * @param green: The green component of the color (0-255).
             * @param blue: The blue component of the color (0-255).
             * @param alpha: The alpha component of the color (0-255).
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture2D(const uchar red, const uchar green, const uchar blue, const uchar alpha = 255,
                      const gl::TextureFilter filter = gl::TextureFilters::Linear, const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates a 1x1 texture from the given color.
             * @param color: The color of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture2D(const Color& color, const gl::TextureFilter filter = gl::TextureFilters::Linear,
                      const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates an empty 2d texture with the given width and height
             * and reserves the memory for it.
             * @param width: The width of the texture.
             * @param height: The height of the texture.
             * @param encoding: The internal format of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture2D(const uint width, const uint height, const gl::TextureEncoding encoding = gl::TextureEncodings::RGBA::Bits8,
                      const gl::TextureFilter filter = gl::TextureFilters::Linear, const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates a 2d texture from the given path to a file.
             * @param path: The path to the texture.
             * @param srgb: Whether the texture should be interpreted as srgb.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture2D(const io::Path& path, const bool srgb, const gl::TextureFilter filter = gl::TextureFilters::Linear,
                      const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Copy constructor.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture2D(const Texture2D&) = delete;
            /** @brief: Move constructor.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture2D(Texture2D&&) noexcept;
            /** @brief: Copy assignment operator.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture2D& operator=(const Texture2D&) = delete;
            /** @brief: Move assignment operator.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture2D& operator=(Texture2D&&) noexcept;

            /** @brief: Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /** @brief: Binds the texture to the current OpenGL rendering context.
             */
            void bind() const override;
            /** @brief: Binds the texture to the given texture unit.
             * @param unit: The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const override;
            /** @brief: Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            void setWrap(const gl::TextureWrap wrap) override;
            /** @brief: Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            void setFilter(const gl::TextureFilter filter) override;
        };

        class Texture3D : public Texture {
            public:
            /** @brief: Creates a cubemap texture from the given color.
             * @param red: The red component of the color (0-255).
             * @param green: The green component of the color (0-255).
             * @param blue: The blue component of the color (0-255).
             * @param alpha: The alpha component of the color (0-255).
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture3D(const uchar red, const uchar green, const uchar blue, const uchar alpha = 255,
                      const gl::TextureFilter filter = gl::TextureFilters::Linear, const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates a cubemap texture from the given color.
             * @param color: The color of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture3D(const Color& color, const gl::TextureFilter filter = gl::TextureFilters::Linear,
                      const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates an empty cubemap with the given width and height
             * for the faces and reserves the memory for it.
             * The format is the internal format of the texture.
             * @param width: The width of the texture.
             * @param height: The height of the texture.
             * @param encoding: The internal format of the texture.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture3D(const uint width, const uint height, const gl::TextureEncoding encoding = gl::TextureEncodings::RGBA::Bits8,
                      const gl::TextureFilter filter = gl::TextureFilters::Linear, const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Creates a cubemap from the given path to a directory containing the faces
             * in 6 distinct png files: right.png, left.png, top.png, bottom.png,
             * front.png, back.png.
             * @param path: The path to the texture.
             * @param srgb: Whether the texture should be interpreted as srgb.
             * @param filter: The filter mode of the texture.
             * @param wrap: The wrap mode of the texture.
             * @return: The created texture.
             */
            Texture3D(const io::Path& path, const bool srgb, const gl::TextureFilter filter = gl::TextureFilters::Linear,
                      const gl::TextureWrap wrap = gl::TextureWraps::Repeat);

            /** @brief: Copy constructor.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture3D(const Texture3D&) = delete;
            /** @brief: Move constructor.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture3D(Texture3D&&) noexcept;
            /** @brief: Copy assignment operator.
             * @param other: The other texture.
             * @return: The copied texture.
             */
            Texture3D& operator=(const Texture3D&) = delete;
            /** @brief: Move assignment operator.
             * @param other: The other texture.
             * @return: The moved texture.
             */
            Texture3D& operator=(Texture3D&&) noexcept;

            /** @brief: Reserves the memory for the texture.
             * @param width: The width of the texture. 0 will use the current width.
             * @param height: The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /** @brief: Binds the texture to the current OpenGL rendering context.
             */
            void bind() const override;
            /** @brief: Binds the texture to the given texture unit.
             * @param unit: The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const override;
            /** @brief: Sets the wrap mode of the texture.
             * @param wrap: The wrap mode.
             */
            void setWrap(const gl::TextureWrap wrap) override;
            /** @brief: Sets the filter mode of the texture.
             * @param filter: The filter mode.
             */
            void setFilter(const gl::TextureFilter filter) override;
        };
    }  // namespace core::gl
}  // namespace cobalt