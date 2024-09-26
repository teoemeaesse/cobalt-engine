/**
 * @file texture.h
 * @brief Texture classes for building and managing OpenGL textures.
 * @author Tomás Marques
 * @date 01-12-2023
 */

#pragma once

#include "core/io/path.h"
#include "core/utils/color.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief A generic texture class for building and managing OpenGL textures.
         */
        class Texture {
            public:
            /**
             * @brief Destroys the texture and frees the memory.
             */
            virtual ~Texture() = default;
            /**
             * @brief Copy constructor.
             * @param other The other texture.
             */
            Texture(const Texture& other) = delete;
            /**
             * @brief Move constructor.
             * @param other The other texture.
             */
            Texture(Texture&& other) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The other texture.
             */
            Texture& operator=(const Texture& other) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other texture.
             */
            Texture& operator=(Texture&& other) noexcept;

            /**
             * @brief Reserves the memory for the texture.
             * @param width The width of the texture. 0 will use the current width.
             * @param height The height of the texture. 0 will use the current height.
             */
            virtual void reserve(const uint width, const uint height) = 0;
            /**
             * @brief Binds the texture to the current OpenGL rendering context.
             */
            virtual void bind() const = 0;
            /**
             * @brief Binds the texture to the given texture unit.
             * @param unit The texture unit to bind the texture to.
             */
            virtual void bindToUnit(const GLuint unit) const = 0;
            /**
             * @brief Sets the wrap mode of the texture.
             * @param wrap The wrap mode.
             */
            virtual void setWrap(const TextureWrap wrap) = 0;
            /**
             * @brief Sets the filter mode of the texture.
             * @param filter The filter mode.
             */
            virtual void setFilter(const TextureFilter filter) = 0;

            /**
             * @brief Returns the GL handle to the texture.
             * @return The GL handle to the texture.
             */
            inline Handle getGLHandle() const { return texture; }
            /**
             * @brief Returns the width of the texture.
             * @return The width of the texture.
             */
            inline uint getWidth() const { return width; }
            /**
             * @brief Returns the height of the texture.
             * @return The height of the texture.
             */
            inline uint getHeight() const { return height; }
            /**
             * @brief Returns the pixel encoding of the texture.
             * @return The pixel encoding of the texture.
             */
            inline TextureEncoding getEncoding() const { return encoding; }

            template <typename TextureType>
            TextureType& as() {
                static_assert(std::is_base_of_v<Texture, TextureType>, "TextureType must derive from Texture");
                return dynamic_cast<TextureType&>(*this);
            }

            protected:
            Handle texture;            ///< The OpenGL handle to the texture.
            std::string source;        ///< The source of the texture.
            TextureFormat format;      ///< The pixel format of the texture.
            TextureEncoding encoding;  ///< The internal format of the texture.
            PixelType pixelType;       ///< The type of the pixels in the texture.
            uint width, height;        ///< The width and height of the texture.

            /**
             * @brief Creates an OpenGL texture.
             * @param encoding The internal format of the texture.
             * @return The created texture.
             */
            Texture(const TextureEncoding encoding);
        };

        /**
         * @brief A 2D texture class for building and managing 2D OpenGL textures.
         */
        class Texture2D : public Texture {
            public:
            /**
             * @brief The default normal map. Points upwards from a flat surface.
             */
            static inline constexpr u_char DEFAULT_NORMAL[] = {
                127,
                127,
                255,
                255,
            };

            /**
             * @brief Creates a 1x1 texture from the given color.
             * @param color The color of the texture.
             * @param encoding The internal encoding of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture2D(const Color& color, const TextureEncoding encoding, const TextureFilter filter = TextureFilters::Linear,
                      const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates a 2d texture from the given data.
             * @param data The data of the texture.
             * @param encoding The internal encoding of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture2D(const void* data, const TextureEncoding encoding, const TextureFilter filter = TextureFilters::Linear,
                      const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates an empty 2d texture with the given width and height and reserves the memory for it.
             * @param width The width of the texture.
             * @param height The height of the texture.
             * @param encoding The internal format of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture2D(const uint width, const uint height, const TextureEncoding encoding = TextureEncodings::RGBA::Bits8,
                      const TextureFilter filter = TextureFilters::Linear, const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates a 2d texture from the given path to a file.
             * @param path The path to the texture.
             * @param srgb Whether the texture should be interpreted as srgb.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture2D(const io::Path& path, const bool srgb, const TextureFilter filter = TextureFilters::Linear,
                      const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Destroys the texture and frees the memory.
             */
            ~Texture2D() override;
            /**
             * @brief Copy constructor.
             * @param other The other texture.
             */
            Texture2D(const Texture2D&) = delete;
            /**
             * @brief Move constructor.
             * @param other The other texture.
             */
            Texture2D(Texture2D&&) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The other texture.
             */
            Texture2D& operator=(const Texture2D&) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other texture.
             */
            Texture2D& operator=(Texture2D&&) noexcept;

            /**
             * @brief Reserves the memory for the texture.
             * @param width The width of the texture. 0 will use the current width.
             * @param height The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /**
             * @brief Binds the texture to the current OpenGL rendering context.
             */
            void bind() const override;
            /**
             * @brief Binds the texture to the given texture unit.
             * @param unit The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const override;
            /**
             * @brief Sets the wrap mode of the texture.
             * @param wrap The wrap mode.
             */
            void setWrap(const TextureWrap wrap) override;
            /**
             * @brief Sets the filter mode of the texture.
             * @param filter The filter mode.
             */
            void setFilter(const TextureFilter filter) override;
        };

        /**
         * @brief A 3D texture class for building and managing 3D OpenGL textures.
         */
        class Texture3D : public Texture {
            public:
            /**
             * @brief Creates a cubemap texture from the given color.
             * @param red The red component of the color (0-255).
             * @param green The green component of the color (0-255).
             * @param blue The blue component of the color (0-255).
             * @param alpha The alpha component of the color (0-255).
             * @param encoding The internal encoding of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture3D(const u_char red, const u_char green, const u_char blue, const u_char alpha = 255,
                      const TextureEncoding encoding = TextureEncodings::RGBA::Bits8, const TextureFilter filter = TextureFilters::Linear,
                      const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates a cubemap texture from the given color.
             * @param color The color of the texture.
             * @param encoding The internal encoding of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture3D(const Color& color, const TextureEncoding encoding = TextureEncodings::RGBA::Bits8,
                      const TextureFilter filter = TextureFilters::Linear, const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates an empty cubemap with the given width and height for the faces and reserves the memory for it. The format is the
             * internal format of the texture.
             * @param width The width of the texture.
             * @param height The height of the texture.
             * @param encoding The internal format of the texture.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture3D(const uint width, const uint height, const TextureEncoding encoding = TextureEncodings::RGBA::Bits8,
                      const TextureFilter filter = TextureFilters::Linear, const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Creates a cubemap from the given path to a directory containing the faces in 6 distinct png files: right.png, left.png,
             * top.png, bottom.png, front.png, back.png.
             * @param path The path to the texture.
             * @param srgb Whether the texture should be interpreted as srgb.
             * @param filter The filter mode of the texture.
             * @param wrap The wrap mode of the texture.
             */
            Texture3D(const io::Path& path, const bool srgb, const TextureFilter filter = TextureFilters::Linear,
                      const TextureWrap wrap = TextureWraps::Repeat);
            /**
             * @brief Destroys the texture and frees the memory.
             */
            ~Texture3D() override;
            /**
             * @brief Copy constructor.
             * @param other The other texture.
             */
            Texture3D(const Texture3D&) = delete;
            /**
             * @brief Move constructor.
             * @param other The other texture.
             */
            Texture3D(Texture3D&&) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The other texture.
             */
            Texture3D& operator=(const Texture3D&) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other texture.
             */
            Texture3D& operator=(Texture3D&&) noexcept;

            /**
             * @brief Reserves the memory for the texture.
             * @param width The width of the texture. 0 will use the current width.
             * @param height The height of the texture. 0 will use the current height.
             */
            void reserve(const uint width, const uint height) override;
            /**
             * @brief Binds the texture to the current OpenGL rendering context.
             */
            void bind() const override;
            /**
             * @brief Binds the texture to the given texture unit.
             * @param unit The texture unit to bind the texture to.
             */
            void bindToUnit(const GLuint unit) const override;
            /**
             * @brief Sets the wrap mode of the texture.
             * @param wrap The wrap mode.
             */
            void setWrap(const TextureWrap wrap) override;
            /**
             * @brief Sets the filter mode of the texture.
             * @param filter The filter mode.
             */
            void setFilter(const TextureFilter filter) override;
        };
    }  // namespace core::gl
}  // namespace cobalt