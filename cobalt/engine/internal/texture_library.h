//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/gl/texture.h"
#include "core/pch.h"


namespace cobalt {
    namespace engine {
        struct TextureID {
            uint index;
            enum class Type {
                TEXTURE_2D,
                TEXTURE_3D
            } type;
        };
        struct TextureCache {
            TextureID::Type type;
            core::Color color;

            friend bool operator==(const TextureCache& lhs, const TextureCache& rhs) {
                return lhs.type == rhs.type && lhs.color == rhs.color;
            }
        };
    }
}

namespace std {
    template <>
    struct hash<cobalt::core::Color> {
        size_t operator()(const cobalt::core::Color& color) const {
            // Example hash function for illustration; you'll need one suited to your Color type
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
}

namespace cobalt {
    namespace engine {
        class TextureLibrary {
            public:
            template<typename T>
            struct TextureEntry {
                static_assert(std::is_base_of<core::Texture, T>::value, "T must be a subclass of core::Texture");
                std::string name;   // The name of the texture.
                T texture;          // The texture.

                /** Creates a new texture entry.
                 * @param name: The name of the texture.
                 * @param texture: The texture.
                 * @return: The texture entry.
                 */
                TextureEntry(const std::string& name, T&& texture) :
                    name(name),
                    texture(std::move(texture))
                {}
            };

            /** Creates an empty texture library.
             * @return: The texture library.
             */
            TextureLibrary();
            /** Destroys the texture library and all textures it contains.
             */
            ~TextureLibrary() = default;

            /** Loads all textures from the given directory.
             * This directory should contain a file called "textures.json" which
             * contains a list of internal texture names and their corresponding
             * texture files.
             * @param texturesDirectory: The directory containing the texture files.
             */
            void loadTextures(const core::Path& texturesDirectory);

            /** Returns the texture ID of the texture with the given name.
             * If the texture does not exist, returns the null texture ID.
             * @param name: The name of the texture.
             * @return: The texture ID.
             */
            const TextureID getTextureID(const std::string& name);

            /** Returns the 2D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::Texture2D& getTexture2D(const TextureID id);
            /** Returns the 2D texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::Texture2D& getTexture2D(const std::string& name);
            /** Returns the 2D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param color: The color of the texture.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */            
            const core::Texture2D& getTexture2D(const core::Color color,
                                                const core::GLTextureFilter filter = core::GLTextureFilter::Linear,
                                                const core::GLTextureWrap wrap = core::GLTextureWrap::Repeat);
            /** Returns the 2D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param red: The red component of the color.
             * @param green: The green component of the color.
             * @param blue: The blue component of the color.
             * @param alpha: The alpha component of the color.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::Texture2D& getTexture2D(const uchar red,
                                                const uchar green,
                                                const uchar blue,
                                                const uchar alpha = 255,
                                                const core::GLTextureFilter filter = core::GLTextureFilter::Linear,
                                                const core::GLTextureWrap wrap = core::GLTextureWrap::Repeat);

            /** Returns the 3D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::Texture3D& getTexture3D(const TextureID id);
            /** Returns the 3D texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::Texture3D& getTexture3D(const std::string& name);
            /** Returns the 3D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param color: The color of the texture.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */            
            const core::Texture3D& getTexture3D(const core::Color color,
                                                const core::GLTextureFilter filter = core::GLTextureFilter::Linear,
                                                const core::GLTextureWrap wrap = core::GLTextureWrap::Repeat);
            /** Returns the 3D texture with the given color.
             * If the texture does not exist, cache and return a new texture.
             * @param red: The red component of the color.
             * @param green: The green component of the color.
             * @param blue: The blue component of the color.
             * @param alpha: The alpha component of the color.
             * @param filter: The filter to use for the texture.
             * @param wrap: The wrap mode to use for the texture.
             * @return: The texture.
             */
            const core::Texture3D& getTexture3D(const uchar red,
                                                const uchar green,
                                                const uchar blue,
                                                const uchar alpha = 255,
                                                const core::GLTextureFilter filter = core::GLTextureFilter::Linear,
                                                const core::GLTextureWrap wrap = core::GLTextureWrap::Repeat);

            /** Returns the texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            const core::Texture& getTexture(const TextureID id);
            /** Returns the texture with the given name.
             * If the texture does not exist, returns a null texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            const core::Texture& getTexture(const std::string& name);

            /** Initializes the singleton instance of the texture library.
             */
            static void init();
            /** Returns the singleton instance of the texture library.
             * @return: The texture library.
             */
            static TextureLibrary& getTextureLibrary();

            private:
            core::Deque<TextureEntry<core::Texture2D>> textures2D;  // The 2D textures in the library.
            core::Deque<TextureEntry<core::Texture3D>> textures3D;  // The cubemap textures in the library.
            core::UMap<TextureCache, TextureID> cache;              // The cache of textures.

            static Scope<TextureLibrary> instance;    // The singleton instance of the texture library.
        };
    }
}

#define CB_TEXTURE_LIBRARY ::cobalt::engine::TextureLibrary::getTextureLibrary()