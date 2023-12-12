//
// Created by tomas on 06-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "engine/internal/texture_library.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace engine {
        std::unique_ptr<TextureLibrary> TextureLibrary::instance;

        TextureLibrary::TextureLibrary() :
            textures(8) {
            textures.push({"null", std::move(core::Texture(1, 1))});
        }
        
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
                textures.push({textureName, std::move(core::Texture(texturePath))});
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
            if (id == 0) {
                CB_WARN("Texture ID 0 is reserved for null textures");
                return textures[0].texture;
            }
            return textures[id - 1].texture;
        }

        void TextureLibrary::init() {
            instance = std::make_unique<TextureLibrary>();
        }

        TextureLibrary& TextureLibrary::getTextureLibrary() {
            return *instance;
        }
    }
}