// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/texture.h"
#include "core/pch.h"

namespace cobalt {
    namespace engine {
        struct TextureID {
            uint index;
            enum class Type { TEXTURE_2D, TEXTURE_3D } type;
        };
        struct TextureCache {
            TextureID::Type type;
            core::Color color;

            friend bool operator==(const TextureCache& lhs, const TextureCache& rhs) { return lhs.type == rhs.type && lhs.color == rhs.color; }
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::core::Color> {
        size_t operator()(const cobalt::core::Color& color) const {
            return hash<float>()(color.r) ^ hash<float>()(color.g) << 1 ^ hash<float>()(color.b) << 2 ^ hash<float>()(color.a) << 3;
        }
    };
    template <>
    struct hash<cobalt::engine::TextureCache> {
        size_t operator()(const cobalt::engine::TextureCache& textureCache) const {
            // Hash individual members and combine
            return hash<cobalt::engine::TextureID::Type>()(textureCache.type) ^ (hash<cobalt::core::Color>()(textureCache.color) << 1);
        }
    };
}  // namespace
   // std

namespace cobalt {
    namespace engine {
        class TextureLibrary {
            public:
            template <typename T>
            struct TextureEntry {
                static_assert(std::is_base_of<core::gl::Texture, T>::value, "T must be a subclass of core::gl::Texture");
                std::string name;  // The name of the texture.
                T texture;         // The texture.

                /**
                 * @brief: Creates a new texture entry.
                 * @param name: The name of the texture.
                 * @param texture: The texture.
                 * @return: The texture entry.
                 */
                TextureEntry(const std::string& name, T&& texture) : name(name), texture(Move(texture)) {}
            };

            /**
             * @brief: Creates an empty texture library.
             * @return: The texture library.
             */
            TextureLibrary();
            /**
             * @brief: Destroys the texture library and all textures it contains.
             */
            ~TextureLibrary() = default;

            /**
             * @brief: Loads all textures from the given directory. This directory should contain a file called "textures.json" which contains a list
             * of internal texture names and their corresponding texture files.
             * @param texturesDirectory: The directory containing the texture files.
             * @return: void
             */
            void loadTextures(const core::io::Path& texturesDirectory);

            /**
             * @brief: Returns the texture ID of the texture with the given name.
             * If the texture does not exist, returns the null texture ID.
             * @param name: The name of the texture.
             * @return: The texture ID.
             */
            const TextureID getTextureID(const std::string& name);

            /**
             * @brief: Returns the 2D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::gl::Texture2D& getTexture2D(const TextureID id);
            /**
             * @brief: Returns the 2D texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::gl::Texture2D& getTexture2D(const std::string& name);
            /**
             * @brief: Returns the 2D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param color: The color of the texture.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::gl::Texture2D& getTexture2D(const core::Color color, const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                                    const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);
            /**
             * @brief: Returns the 2D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param red: The red component of the color.
             * @param green: The green component of the color.
             * @param blue: The blue component of the color.
             * @param alpha: The alpha component of the color.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::gl::Texture2D& getTexture2D(const uchar red, const uchar green, const uchar blue, const uchar alpha = 255,
                                                    const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                                    const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);

            /**
             * @brief: Returns the 3D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::gl::Texture3D& getTexture3D(const TextureID id);
            /**
             * @brief: Returns the 3D texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::gl::Texture3D& getTexture3D(const std::string& name);
            /**
             * @brief: Returns the 3D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param color: The color of the texture.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::gl::Texture3D& getTexture3D(const core::Color color, const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                                    const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);
            /**
             * @brief: Returns the 3D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param red: The red component of the color.
             * @param green: The green component of the color.
             * @param blue: The blue component of the color.
             * @param alpha: The alpha component of the color.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::gl::Texture3D& getTexture3D(const uchar red, const uchar green, const uchar blue, const uchar alpha = 255,
                                                    const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                                    const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);

            /**
             * @brief: Returns the texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::gl::Texture& getTexture(const TextureID id);
            /**
             * @brief: Returns the texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::gl::Texture& getTexture(const std::string& name);

            /**
             * @brief: Initializes the singleton instance of the texture library.
             * @return: void
             */
            static void init();
            /**
             * @brief: Returns the singleton instance of the texture library.
             * @return: The texture library.
             */
            static TextureLibrary& getTextureLibrary();

            private:
            Deque<TextureEntry<core::gl::Texture2D>> textures2D;  // The 2D textures in the library.
            Deque<TextureEntry<core::gl::Texture3D>> textures3D;  // The cubemap textures in the library.
            UMap<TextureCache,
                 TextureID> cache;  // The cache of textures.

            static Scope<TextureLibrary> instance;  // The singleton instance of the texture library.
        };
    }  // namespace engine
}  // namespace cobalt

#define CB_TEXTURE_LIBRARY ::cobalt::engine::TextureLibrary::getTextureLibrary()