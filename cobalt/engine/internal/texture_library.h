//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/gl/texture.h"
#include "core/pch.h"


namespace cobalt {
    namespace engine {
        struct TextureID {
            core::uint64 index;
            enum class Type {
                TEXTURE_2D,
                TEXTURE_3D
            } type;
        };

        class TextureLibrary {
            public:
            template<typename T>
            struct TextureEntry {
                static_assert(std::is_base_of<core::Texture, T>::value, "T must be a subclass of core::Texture");
                std::string name;   // The name of the texture.
                T texture;          // The texture.
            };

            /* Creates an empty texture library.
             * @return: The texture library.
             */
            TextureLibrary();
            /* Destroys the texture library and all textures it contains.
             */
            ~TextureLibrary() = default;

            /* Loads all textures from the given directory.
             * This directory should contain a file called "textures.json" which
             * contains a list of internal texture names and their corresponding
             * texture files.
             * @param texturesDirectory: The directory containing the texture files.
             */
            void loadTextures(const core::Path& texturesDirectory);

            /* Returns the texture ID of the texture with the given name.
             * If the texture does not exist, returns the null texture ID.
             * @param name: The name of the texture.
             */
            const TextureID getTextureID(const std::string& name);

            /* Returns the 2D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             */
            const core::Texture2D& getTexture2D(const TextureID id);

            /* Returns the 3D texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             */
            const core::Texture3D& getTexture3D(const TextureID id);

            /* Initializes the singleton instance of the texture library.
             */
            static void init();
            /* Returns the singleton instance of the texture library.
             * @return: The texture library.
             */
            static TextureLibrary& getTextureLibrary();

            private:
            core::Vector<TextureEntry<core::Texture2D>> textures2D; // The 2D textures in the library.
            core::Vector<TextureEntry<core::Texture3D>> textures3D; // The cubemap textures in the library.

            static std::unique_ptr<TextureLibrary> instance;    // The singleton instance of the texture library.
        };
    }
}

#define CB_TEXTURE_LIBRARY ::cobalt::engine::TextureLibrary::getTextureLibrary()