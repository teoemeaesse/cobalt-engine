// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/texture.h"
#include "engine/internal/internal_exception.h"

namespace cobalt {
    namespace engine {
        class TextureLibrary;

        class TextureID {
            friend class TextureLibrary;

            public:
            /**
             * @brief Creates a new texture ID.
             * @param handle The handle of the texture.
             * @param name The name of the texture.
             * @param owner The texture library that owns the texture.
             */
            TextureID(const uint handle, const std::string& name, TextureLibrary& owner) noexcept;
            /**
             * @brief Default destructor.
             */
            ~TextureID() noexcept = default;
            /**
             * @brief Default copy constructor.
             * @param other The other texture ID.
             */
            TextureID(const TextureID& other) noexcept = default;
            /**
             * @brief Default move constructor.
             * @param other The other texture ID.
             */
            TextureID(TextureID&& other) noexcept = default;
            /**
             * @brief Default copy assignment operator.
             * @param other The other texture ID.
             * @return The new texture ID.
             */
            TextureID& operator=(const TextureID& other) noexcept = delete;
            /**
             * @brief Default move assignment operator.
             * @param other The other texture ID.
             * @return The new texture ID.
             */
            TextureID& operator=(TextureID&& other) noexcept = delete;

            /**
             * @brief Checks if two texture IDs are equal.
             * @param other The other texture ID.
             * @return True if the handles are equal, false otherwise.
             */
            bool operator==(const TextureID& other) const noexcept;
            /**
             * @brief Checks if two texture IDs are not equal.
             * @param other The other texture ID.
             * @return True if the handles are not equal, false otherwise.
             */
            bool operator!=(const TextureID& other) const noexcept;

            /**
             * @brief Returns the handle of the texture.
             * @return The handle.
             */
            const uint getHandle() const noexcept;
            /**
             * @brief Returns the name of the texture.
             * @return The name.
             */
            const std::string& getName() const noexcept;
            /**
             * @brief Returns the texture.
             * @return The texture.
             */
            core::gl::Texture& getTexture() noexcept;

            private:
            uint handle;
            std::string name;
            TextureLibrary& owner;
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::engine::TextureID> {
        size_t operator()(const cobalt::engine::TextureID& id) const { return hash<uint>()(id.getHandle()); }
    };
}  // namespace std

namespace cobalt {
    namespace engine {
        class TextureLibrary : public core::ecs::Resource {
            public:
            /**
             * @brief Default constructor.
             */
            TextureLibrary() = default;
            /**
             * @brief Default destructor.
             */
            ~TextureLibrary() = default;

            /**
             * @brief Loads all textures from the given directory. This directory should contain a file called "textures.json" which contains a list
             * of internal texture names and their corresponding texture files.
             * @param texturesDirectory The directory containing the texture files.
             */
            void loadTextures(const core::io::Path& texturesDirectory);

            /**
             * @brief Returns the texture ID of the texture with the given name.
             * @param name The name of the texture.
             * @return The texture ID.
             */
            TextureID& getTextureID(const std::string& name);

            /**
             * @brief Returns the texture with the given ID.
             * @param id The ID of the texture.
             * @return The texture.
             * @throws core::ecs::PluginException<TexturePlugin, TextureLibrary> If the texture does not exist.
             */
            core::gl::Texture& getTexture(const TextureID& id);

            /**
             * @brief Returns the texture with the given name.
             * @param name The name of the texture.
             * @return The texture.
             * @throws core::ecs::PluginException<TexturePlugin, TextureLibrary> If the texture does not exist.
             */
            core::gl::Texture& getTexture(const std::string& name);

            /**
             * @brief Creates a new texture and adds it to the library.
             * @param name The name of the texture.
             * @param data The data of the texture.
             * @param encoding The encoding of the texture.
             * @param filter The filter of the texture.
             * @param wrap The wrap of the texture.
             * @return The ID of the new texture.
             */
            TextureID& makeTexture(const std::string& name, const void* data, const core::gl::TextureEncoding encoding,
                                   const core::gl::TextureFilter filter = core::gl::TextureFilters::Linear,
                                   const core::gl::TextureWrap wrap = core::gl::TextureWraps::Repeat);

            private:
            UMap<TextureID, Scope<core::gl::Texture>> textures;  // All the textures in the library.
            UMap<std::string, TextureID> textureNames;           // A mapping of texture names to their corresponding IDs.
        };
    }  // namespace engine
}  // namespace cobalt