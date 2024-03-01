// Created by tomas on
// 06-12-2023

#include "engine/internal/texture_library.h"

namespace cobalt {
    namespace engine {
        Scope<TextureLibrary> TextureLibrary::instance;

        TextureID::TextureID() noexcept : index(0), type(TextureID::Type::TEXTURE_2D) {}

        TextureID::TextureID(const uint index, const Type type) noexcept : index(index), type(type) {}

        TextureEntry::TextureEntry() noexcept : id(CB_DEFAULT_TEXTURE_ID), texture(nullptr) {}

        TextureEntry::TextureEntry(const TextureID& id, Scope<core::gl::Texture>&& texture) noexcept : id(id), texture(Move(texture)) {}

        TextureEntry::TextureEntry(TextureEntry&& other) noexcept : id(other.id), texture(Move(other.texture)) {}

        const TextureID TextureEntry::getID() const { return id; }

        TextureLibrary::TextureLibrary() {
            store.emplace(std::piecewise_construct, std::forward_as_tuple((TextureID)CB_DEFAULT_TEXTURE_ID),
                          std::forward_as_tuple((TextureID)CB_DEFAULT_TEXTURE_ID, Move(createScope<core::gl::Texture2D>(1, 1))));
        }

        void TextureLibrary::loadTextures(const core::io::Path& texturesDirectory) {
            core::io::Path texturesJsonPath = texturesDirectory;
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
                std::string textureType = textureJson["type"].get<std::string>();
                bool isSrgb = textureJson["srgb"].get<bool>();
                core::io::Path texturePath = texturesDirectory + textureJson["src"].get<std::string>();
                if (textureType == "2d") {
                    CB_INFO("Loading 2D texture \"{0}\" @{1}", textureName, texturePath.getFileName());
                    const TextureID id = TextureID((uint)store.size(), TextureID::Type::TEXTURE_2D);
                    store.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                                  std::forward_as_tuple(id, Move(createScope<core::gl::Texture2D>(texturePath, isSrgb))));
                    mapping.emplace(textureName, id);
                    continue;
                } else if (textureType == "3d") {
                    CB_INFO("Loading cubemap texture \"{0}\" @{1}", textureName, texturePath.getFileName());
                    const TextureID id = TextureID((uint)store.size(), TextureID::Type::TEXTURE_3D);
                    store.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                                  std::forward_as_tuple(id, Move(createScope<core::gl::Texture3D>(texturePath, isSrgb))));
                    mapping.emplace(textureName, id);
                    continue;
                }
            }
        }

        const TextureID TextureLibrary::getTextureID(const std::string& name) {
            if (mapping.find(name) != mapping.end()) {
                return mapping[name];
            }
            return CB_DEFAULT_TEXTURE_ID;
        }

        const TextureID TextureLibrary::makeTexture(const std::string& name, const void* data, const core::gl::TextureEncoding encoding,
                                                    const core::gl::TextureFilter filter, const core::gl::TextureWrap wrap) {
            if (getTextureID(name) != (TextureID)CB_DEFAULT_TEXTURE_ID) {
                return getTextureID(name);
            }
            const TextureID id = TextureID((uint)store.size(), TextureID::Type::TEXTURE_2D);
            store.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                          std::forward_as_tuple(id, Move(createScope<core::gl::Texture2D>(data, encoding, filter, wrap))));
            mapping.emplace(name, id);
            return id;
        }

        void TextureLibrary::init() { instance = createScope<TextureLibrary>(); }

        TextureLibrary& TextureLibrary::getTextureLibrary() { return *instance; }
    }  // namespace engine
}  // namespace cobalt