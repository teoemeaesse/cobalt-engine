//
// Created by tomas on 06-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "engine/internal/texture_library.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace engine {
        TextureLibrary::TextureLibrary()
            : textures(8) {}
        
        void TextureLibrary::loadTextures(const core::Path& texturesDirectory) {
            core::Path texturesJsonPath = texturesDirectory;
            texturesJsonPath += "textures.json";
            if (!texturesJsonPath.exists()) {
                CB_WARN("No textures.json file found in textures directory: {}", texturesDirectory.getPath());
                return;
            }
            std::ifstream texturesJsonFile(texturesJsonPath.getPath());
            nlohmann::json texturesJson = nlohmann::json::parse(texturesJsonFile);
            CB_INFO("Loading textures from: {}", texturesDirectory.getPath());
            CB_INFO("Found {} textures", texturesJson.size());
            for (auto it = texturesJson.begin(); it != texturesJson.end(); ++it) {
                std::string textureName = it.key();
                nlohmann::json textureJson = it.value();
                core::Path texturePath = texturesDirectory + textureJson["src"].get<std::string>();
                CB_INFO("Loading texture: {}", textureName);
                CB_INFO("From source: {}", texturePath.getFileName());
                textures.push({textureName, core::Texture(texturePath)});
            }
        }

        const TextureID TextureLibrary::getTextureID(const std::string& name) {
            for (core::uint64 i = 0; i < textures.getSize(); i++) {
                if (textures[i].name == name) {
                    return i + 1;
                }
            }
            return 0;
        }

        const core::Texture& TextureLibrary::getTexture(const TextureID id) {
            return textures[id - 1].texture;
        }
    }
}