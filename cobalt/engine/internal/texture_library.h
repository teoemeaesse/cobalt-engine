//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/containers/vector.h"
#include "core/io/path.h"
#include "core/gl/texture.h"


namespace cobalt {
    namespace engine {
        using TextureID = core::uint64;

        class TextureLibrary {
            public:
            struct TextureEntry {
                std::string name;                       // The name of the texture.
                std::unique_ptr<core::Texture> texture; // The texture.
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
             * If the texture does not exist, returns 0.
             * @param name: The name of the texture.
             */
            const TextureID getTextureID(const std::string& name);

            /* Returns the texture with the given ID.
             * If the texture does not exist, returns a null texture.
             * @param id: The ID of the texture.
             */
            const core::Texture& getTexture(const TextureID id);

            private:
            core::Vector<TextureEntry> textures;  // The textures in the library.
        };
    }
}