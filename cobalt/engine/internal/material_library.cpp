//
// Created
// by
// tomas
// on
// 24-12-2023.
//

#include "engine/internal/material_library.h"

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

        core::Material& MaterialLibrary::getMaterial(const MaterialID id) {
            if (id >= materials.size() || id < 0) {
                CB_WARN("Material ID {0} out of bounds, returning default material", id);
                return materials[0].material;
            }
            return materials[id].material;
        }

        const MaterialID MaterialLibrary::makePBR(const std::string& name, const TextureID& albedo, const TextureID& normal, const TextureID& mrao) {
            materials.emplace_back(name, core::Material(CB_SHADER_LIBRARY.getShader("pbr"), CB_TEXTURE_LIBRARY.getTexture2D(albedo),
                                                        CB_TEXTURE_LIBRARY.getTexture2D(normal), CB_TEXTURE_LIBRARY.getTexture2D(mrao)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makePBR(const std::string& name, const core::Color albedo, const float metallic, const float roughness,
                                                  const float ao) {
            materials.emplace_back(
                name, core::Material(CB_SHADER_LIBRARY.getShader("pbr"), CB_TEXTURE_LIBRARY.getTexture2D(albedo),
                                     CB_TEXTURE_LIBRARY.getTexture2D(127, 127, 255),
                                     CB_TEXTURE_LIBRARY.getTexture2D((uchar)(metallic * 255.0f), (uchar)(roughness * 255.0f), (uchar)(ao * 255.0f))));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeFromShader(const std::string& name, const ShaderID& shader) {
            materials.emplace_back(name,
                                   core::Material(CB_SHADER_LIBRARY.getShader(shader), CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255),
                                                  CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255), CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255)));
            return materials.size() - 1;
        }

        const MaterialID MaterialLibrary::makeFromShader(const std::string& name, const std::string& shader) {
            materials.emplace_back(name,
                                   core::Material(CB_SHADER_LIBRARY.getShader(shader), CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255),
                                                  CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255), CB_TEXTURE_LIBRARY.getTexture2D(255, 255, 255)));
            return materials.size() - 1;
        }

        void MaterialLibrary::init() { instance = createScope<MaterialLibrary>(); }

        MaterialLibrary& MaterialLibrary::getMaterialLibrary() { return *instance; }
    }  // namespace engine
}  // namespace
   // cobalt