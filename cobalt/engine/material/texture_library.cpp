// Created by tomas on
// 06-12-2023

#include "core/ecs/exception.h"
#include "engine/material/plugin.h"

namespace cobalt {
    namespace engine {
        TextureID::TextureID(const uint handle, const std::string& name, TextureLibrary& owner) noexcept : handle(handle), name(name), owner(owner) {}

        bool TextureID::operator==(const TextureID& other) const noexcept { return handle == other.handle; }

        bool TextureID::operator!=(const TextureID& other) const noexcept { return handle != other.handle; }

        const uint TextureID::getHandle() const noexcept { return handle; }

        const std::string& TextureID::getName() const noexcept { return name; }

        core::gl::Texture& TextureID::getTexture() noexcept { return owner.getTexture(*this); }

        void TextureLibrary::loadTextures(const core::io::Path& texturesDirectory) {
            core::io::Path texturesJsonPath = texturesDirectory;
            texturesJsonPath += "textures.json";
            if (!texturesJsonPath.exists()) {
                CB_WARN("No textures.json file found in the textures directory: {}", texturesDirectory.getPath());
                return;
            }
            std::ifstream texturesJsonFile(texturesJsonPath.getPath());
            nlohmann::json texturesJson = nlohmann::json::parse(texturesJsonFile);
            CB_INFO("Loading textures from: {}", texturesDirectory.getPath());
            CB_INFO("Found {} textures", texturesJson.size());
            for (auto it = texturesJson.begin(); it != texturesJson.end(); ++it) {
                std::string textureName = it.key();
                nlohmann::json textureJson = it.value();
                std::string textureType = textureJson["type"].get<std::string>();
                bool isSrgb = textureJson["srgb"].get<bool>();
                core::io::Path texturePath = texturesDirectory + textureJson["src"].get<std::string>();
                if (textureType == "2d") {
                    CB_INFO("Loading 2D texture \"{0}\" @{1}", textureName, texturePath.getFileName());
                    TextureID id(textures.size(), textureName, *this);
                    textureNames.emplace(textureName, id);
                    textures.erase(id);
                    textures.emplace(id, Move(CreateScope<core::gl::Texture2D>(texturePath, isSrgb)));
                    continue;
                } else if (textureType == "3d") {
                    CB_INFO("Loading cubemap texture \"{0}\" @{1}", textureName, texturePath.getFileName());
                    TextureID id(textures.size(), textureName, *this);
                    textureNames.emplace(textureName, id);
                    textures.erase(id);
                    textures.emplace(id, Move(CreateScope<core::gl::Texture3D>(texturePath, isSrgb)));
                    continue;
                }
            }
        }

        TextureID& TextureLibrary::getTextureID(const std::string& name) {
            try {
                return textureNames.at(name);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, TextureLibrary>("Texture with name " + name + " not found");
            }
        }

        core::gl::Texture& TextureLibrary::getTexture(const TextureID& id) {
            try {
                return *textures.at(id);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, TextureLibrary>("Texture with ID " + std::to_string(id.getHandle()) + " not found");
            }
        }

        core::gl::Texture& TextureLibrary::getTexture(const std::string& name) {
            try {
                return *textures.at(textureNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, TextureLibrary>("Texture with name " + name + " not found");
            }
        }

        TextureID& TextureLibrary::makeTexture(const std::string& name, const void* data, const core::gl::TextureEncoding encoding,
                                               const core::gl::TextureFilter filter, const core::gl::TextureWrap wrap) {
            if (textureNames.find(name) != textureNames.end()) {
                return getTextureID(name);
            }
            TextureID id(textures.size(), name, *this);
            textureNames.emplace(name, id);
            textures.erase(id);
            textures.emplace(id, Move(CreateScope<core::gl::Texture2D>(data, encoding, filter, wrap)));
            return textureNames.at(name);
        }
    }  // namespace engine
}  // namespace cobalt