// Created by tomas on
// 24-12-2023

#include "engine/internal/material_library.h"

#include "material_library.h"

namespace cobalt {
    namespace engine {
        Scope<MaterialLibrary> MaterialLibrary::instance;

        MaterialLibrary::MaterialLibrary() {}

        const MaterialID MaterialLibrary::getMaterialID(const std::string& name) {
            for (uint64 i = 0; i < materials.size(); i++) {
                if (materials[i].name == name) {
                    return i;
                }
            }
            return 0;
        }

        core::gfx::Material& MaterialLibrary::getMaterial(const MaterialID id) {
            if (id >= materials.size() || id < 0) {
                CB_WARN("Material ID {0} out of bounds, returning default material", id);
                return materials[0].material;
            }
            return materials[id].material;
        }

        const MaterialID MaterialLibrary::makePBR(const std::string& name, const TextureID& albedo, const TextureID& normal, const TextureID& mrao) {
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterialPBR(CB_SHADER_LIBRARY.getShader("pbr"),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(albedo),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(normal),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(mrao)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makePBR(const std::string& name, const core::Color albedo, const float metallic, const float roughness,
                                                  const float ao) {
            TextureID normalID = CB_TEXTURE_LIBRARY.makeTexture("CB_default-normal", (void*)core::gl::Texture2D::DEFAULT_NORMAL,
                                                                core::gl::TextureEncodings::RGBA::Bits8);
            uchar albedoData[4];
            albedo.toUChar(albedoData);
            TextureID albedoID = CB_TEXTURE_LIBRARY.makeTexture(albedo.toString(), (void*)&albedoData, core::gl::TextureEncodings::RGBA::Bits8);
            core::Color mrao(metallic, roughness, ao);
            uchar mraoData[4];
            mrao.toUChar(mraoData);
            TextureID mraoID = CB_TEXTURE_LIBRARY.makeTexture(mrao.toString(), (void*)&mraoData, core::gl::TextureEncodings::RGB::Bits8);
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterialPBR(CB_SHADER_LIBRARY.getShader("pbr"),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(albedoID),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(normalID),
                                                                                       CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(mraoID)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeUnlit(const std::string& name, const TextureID& color) {
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterialUnlit(CB_SHADER_LIBRARY.getShader("unlit"),
                                                                                         CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(color)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeUnlit(const std::string& name, const core::Color color) {
            TextureID colorID = CB_TEXTURE_LIBRARY.makeTexture(color.toString(), (void*)&color, core::gl::TextureEncodings::RGBA::Bits8);
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterialUnlit(
                                             CB_SHADER_LIBRARY.getShader("unlit"), CB_TEXTURE_LIBRARY.getTexture<core::gl::Texture2D>(colorID)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeFromShader(const std::string& name, const ShaderID& shader,
                                                         const UMap<std::string, const core::gl::Texture2D&>& textures) {
            UMap<std::string, const core::gl::Texture&> textureMap;
            for (auto& texture : textures) {
                textureMap.emplace(texture.first, texture.second);
            }
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterial(CB_SHADER_LIBRARY.getShader(shader), textureMap));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeFromShader(const std::string& name, const std::string& shader,
                                                         const UMap<std::string, const core::gl::Texture2D&>& textures) {
            UMap<std::string, const core::gl::Texture&> textureMap;
            for (auto& texture : textures) {
                textureMap.emplace(texture.first, texture.second);
            }
            materials.emplace_back(name, core::gfx::MaterialFactory::createMaterial(CB_SHADER_LIBRARY.getShader(shader), textureMap));
            return materials.size() - 1;
        }

        void MaterialLibrary::init() { instance = CreateScope<MaterialLibrary>(); }

        MaterialLibrary& MaterialLibrary::getMaterialLibrary() { return *instance; }
    }  // namespace engine
}  // namespace cobalt