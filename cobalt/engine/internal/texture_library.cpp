//
// Created by tomas on 06-12-2023.
//

#include "engine/internal/texture_library.h"
#include "engine/internal/internal_exception.h"
#include "core/pch.h"


namespace cobalt {
    namespace engine {
        core::Scope<TextureLibrary> TextureLibrary::instance;

        TextureLibrary::TextureLibrary() {
            textures2D.emplace_back("null", std::move(core::TextureBuilder().setDimensions(1, 1).setIsColor(true).setChannels(4).buildEmpty2D()));
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
                std::string textureType = textureJson["type"].get<std::string>();
                bool isSrgb = textureJson["srgb"].get<bool>();
                core::Path texturePath = texturesDirectory + textureJson["src"].get<std::string>();
                if (textureType == "2d") {
                    CB_INFO("Loading 2D texture: {}", textureName);
                    CB_INFO("From source file: {}", texturePath.getFileName());
                    textures2D.emplace_back(textureName, std::move(core::TextureBuilder().setIsSrgb(isSrgb).buildFromSource2D(texturePath)));
                    continue;
                }
                else if (textureType == "3d") {
                    CB_INFO("Loading cubemap: {}", textureName);
                    CB_INFO("From source directory: {}", texturePath.getFileName());
                    textures3D.emplace_back(textureName, std::move(core::TextureBuilder().setIsSrgb(isSrgb).buildFromSource3D(texturePath)));
                    continue;
                }
            }
        }

        const TextureID TextureLibrary::getTextureID(const std::string& name) {
            for (core::uint i = 0; i < textures2D.size(); i++) {
                if (textures2D[i].name == name) {
                    return {i, TextureID::Type::TEXTURE_2D};
                }
            }
            for (core::uint i = 0; i < textures3D.size(); i++) {
                if (textures3D[i].name == name) {
                    return {i, TextureID::Type::TEXTURE_3D};
                }
            }
            return {0, TextureID::Type::TEXTURE_2D};
        }

        const core::Texture& TextureLibrary::getTexture(const TextureID id) {
            if (id.type == TextureID::Type::TEXTURE_2D) {
                return getTexture2D(id);
            }
            if (id.type == TextureID::Type::TEXTURE_3D) {
                return getTexture3D(id);
            }
            return textures2D[0].texture;
        }

        const core::Texture& TextureLibrary::getTexture(const std::string& name) {
            return getTexture(getTextureID(name));
        }

        void TextureLibrary::init() {
            instance = std::make_unique<TextureLibrary>();
        }

        TextureLibrary& TextureLibrary::getTextureLibrary() {
            return *instance;
        }

        const core::Texture2D& TextureLibrary::getTexture2D(const TextureID id) {
            if(id.type == TextureID::Type::TEXTURE_2D) {
                if (id.index >= textures2D.size() || id.index < 0) {
                    CB_WARN("Texture ID {} is out of bounds", id.index);
                    return textures2D[0].texture;
                }
                return textures2D[id.index].texture;
            }
            throw InternalException("Texture ID is not a 2D texture");
        }

        const core::Texture2D& TextureLibrary::getTexture2D(const std::string& name) {
            return getTexture2D(getTextureID(name));
        }

        const core::Texture2D& TextureLibrary::getTexture2D(const core::Color color,
                                                            const core::GLTextureFilter filter,
                                                            const core::GLTextureWrap wrap) {
            TextureCache entry = {TextureID::Type::TEXTURE_2D, color};
            if (cache.find(entry) == cache.end()) {
                textures2D.emplace_back(core::colorToString(color), std::move(core::Texture2D(color, filter, wrap)));
                cache[entry] = {(uint) textures2D.size() - 1, TextureID::Type::TEXTURE_2D};
            }
            return getTexture2D(cache[entry]);
        }

        const core::Texture2D& TextureLibrary::getTexture2D(const core::uchar red,
                                                            const core::uchar green,
                                                            const core::uchar blue,
                                                            const core::uchar alpha,
                                                            const core::GLTextureFilter filter,
                                                            const core::GLTextureWrap wrap) {
            core::Color color = COLOR(red, green, blue, alpha);
            TextureCache entry = {TextureID::Type::TEXTURE_2D, color};
            if (cache.find(entry) == cache.end()) {
                textures2D.emplace_back(core::colorToString(color), std::move(core::Texture2D(red, green, blue, alpha, filter, wrap)));
                cache[entry] = {(uint) textures2D.size() - 1, TextureID::Type::TEXTURE_2D};
            }
            return getTexture2D(cache[entry]);
        }

        const core::Texture3D& TextureLibrary::getTexture3D(const TextureID id) {
            if(id.type == TextureID::Type::TEXTURE_3D) {
                if (id.index >= textures3D.size() || id.index < 0) {
                    CB_WARN("Texture ID {} is out of bounds", id.index);
                    return textures3D[0].texture;
                }
                return textures3D[id.index].texture;
            }
            throw InternalException("Texture ID is not a 3D texture");
        }

        const core::Texture3D& TextureLibrary::getTexture3D(const std::string& name) {
            return getTexture3D(getTextureID(name));
        }

        const core::Texture3D& TextureLibrary::getTexture3D(const core::Color color,
                                                            const core::GLTextureFilter filter,
                                                            const core::GLTextureWrap wrap) {
            TextureCache entry = {TextureID::Type::TEXTURE_3D, color};
            if (cache.find(entry) == cache.end()) {
                textures3D.emplace_back(core::colorToString(color), std::move(core::Texture3D(color, filter, wrap)));
                cache[entry] = {(uint) textures3D.size() - 1, TextureID::Type::TEXTURE_3D};
            }
            return getTexture3D(cache[entry]);
        }

        const core::Texture3D& TextureLibrary::getTexture3D(const core::uchar red,
                                                            const core::uchar green,
                                                            const core::uchar blue,
                                                            const core::uchar alpha,
                                                            const core::GLTextureFilter filter,
                                                            const core::GLTextureWrap wrap) {
            core::Color color = COLOR(red, green, blue, alpha);
            TextureCache entry = {TextureID::Type::TEXTURE_3D, color};
            if (cache.find(entry) == cache.end()) {
                textures3D.emplace_back(core::colorToString(color), std::move(core::Texture3D(red, green, blue, alpha, filter, wrap)));
                cache[entry] = {(uint) textures3D.size() - 1, TextureID::Type::TEXTURE_3D};
            }
            return getTexture3D(cache[entry]);
        }
    }
}