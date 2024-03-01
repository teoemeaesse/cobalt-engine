// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/texture.h"
#include "engine/internal/internal_exception.h"

#define CB_DEFAULT_TEXTURE_ID \
    { 0, TextureID::Type::TEXTURE_2D }

namespace cobalt {
    namespace engine {
        struct TextureID {
            uint index;
            enum class Type { TEXTURE_2D, TEXTURE_3D } type;

            TextureID() noexcept;
            TextureID(const uint index, const Type type) noexcept;
            TextureID(const TextureID& other) noexcept = default;
            TextureID(TextureID&& other) noexcept = default;
            TextureID& operator=(const TextureID& other) noexcept = default;
            TextureID& operator=(TextureID&& other) noexcept = default;

            bool operator==(const TextureID& other) const { return index == other.index && type == other.type; }
            bool operator!=(const TextureID& other) const { return !(*this == other); }
        };
        class TextureEntry {
            public:
            /**
             * @brief: Creates an empty texture entry.
             * @return: The texture entry.
             */
            TextureEntry() noexcept;
            /**
             * @brief: Creates a new texture entry.
             * @param id: The ID of the texture.
             * @param texture: The texture itself.
             * @return: The texture entry.
             */
            TextureEntry(const TextureID& id, Scope<core::gl::Texture>&& texture) noexcept;
            /**
             * @brief: Copy constructor.
             * @param other: The other texture entry.
             * @return: The new texture entry.
             */
            TextureEntry(const TextureEntry& other) noexcept = delete;
            /**
             * @brief: Copy assignment operator.
             * @param other: The other texture entry.
             * @return: The new texture entry.
             */
            TextureEntry& operator=(const TextureEntry& other) noexcept = delete;

            /**
             * @brief: Move constructor.
             * @param other: The other texture entry.
             * @return: The new texture entry.
             */
            TextureEntry(TextureEntry&& other) noexcept;
            /**
             * @brief: Move assignment operator.
             * @param other: The other texture entry.
             * @return: The new texture entry.
             */
            TextureEntry& operator=(TextureEntry&& other) noexcept = delete;

            /**
             * @brief: Casts the texture to a given type.
             * @tparam TextureType: The type of the texture.
             * @return: The texture.
             */
            template <typename TextureType>
            const TextureType& getTexture() const {
                return dynamic_cast<const TextureType&>(*texture);
            }

            /**
             * @brief: Returns the ID of the texture.
             * @return: The ID.
             */
            const TextureID getID() const;

            private:
            const TextureID id;                // The ID of the texture.
            Scope<core::gl::Texture> texture;  // The stored texture.
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::engine::TextureID> {
        size_t operator()(const cobalt::engine::TextureID& id) const { return hash<cobalt::engine::TextureID::Type>()(id.type); }
    };
}  // namespace std

namespace cobalt {
    namespace engine {
        class TextureLibrary {
            public:
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
             * @brief: Returns the texture ID of the texture with the given name. If the texture does not exist, returns the default texture ID.
             * @param name: The name of the texture.
             * @return: The texture ID.
             */
            const TextureID getTextureID(const std::string& name);

            /**
             * @brief: Returns the texture with the given ID. If the texture does not exist, returns a default texture.
             * @tparam TextureType: The type of the texture.
             * @param id: The ID of the texture.
             * @return: The texture.
             */
            template <typename TextureType>
            const TextureType& getTexture(const TextureID id) {
                if (store.find(id) == store.end()) {
                    CB_WARN("Trying to get texture ID {} but it does not exist", id.index);
                }
                return store.at(id).getTexture<TextureType>();
            }

            /**
             * @brief: Returns the texture with the given name. If the texture does not exist, returns a default texture.
             * @tparam TextureType: The type of the texture.
             * @param name: The name of the texture.
             * @return: The texture.
             */
            template <typename TextureType>
            const TextureType& getTexture(const std::string& name) {
                return getTexture<TextureType>(getTextureID(name));
            }

            /**
             * @brief: Creates a new texture and adds it to the library.
             * @param name: The name of the texture.
             * @param data: The data of the texture.
             * @param encoding: The encoding of the texture.
             * @param filter: The filter of the texture.
             * @param wrap: The wrap of the texture.
             * @return: The ID of the new texture.
             */
            const TextureID makeTexture(const std::string& name, const void* data, const core::gl::TextureEncoding encoding,
                                        const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                        const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);

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
            UMap<TextureID, TextureEntry> store;   // All the textures in the library.
            UMap<std::string, TextureID> mapping;  // A mapping of texture names to their corresponding IDs.

            static Scope<TextureLibrary> instance;  // The singleton instance of the texture library.
        };
    }  // namespace engine
}  // namespace cobalt

#define CB_TEXTURE_LIBRARY ::cobalt::engine::TextureLibrary::getTextureLibrary()