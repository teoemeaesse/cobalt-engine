//
// Created by tomas on 24-12-2023.
//

#include "engine/internal/material_library.h"
#include "engine/internal/texture_library.h"
#include "engine/internal/shader_library.h"


namespace cobalt {
    namespace engine {
        core::Scope<MaterialLibrary> MaterialLibrary::instance;

        MaterialLibrary::MaterialLibrary() :
            materials(8)
        {}

        const MaterialID MaterialLibrary::getMaterialID(const std::string& name) {
            for (core::uint64 i = 0; i < materials.getSize(); i++) {
                if (materials[i].name == name) {
                    return i;
                }
            }
            return 0;
        }

        core::Material& MaterialLibrary::getMaterial(const MaterialID id) {
            return materials[id].material;
        }

        const MaterialID MaterialLibrary::makePBR(
            const std::string& name,
            const TextureID& albedo,
            const TextureID& normal,
            const TextureID& mrao) {
            MaterialEntry entry = { name, core::Material(
                CB_SHADER_LIBRARY.getShader("pbr"),
                CB_TEXTURE_LIBRARY.getTexture(albedo),
                CB_TEXTURE_LIBRARY.getTexture(normal),
                CB_TEXTURE_LIBRARY.getTexture(mrao)) };
            materials.push(entry);
            return materials.getSize() - 1;
        }

        const MaterialID MaterialLibrary::makePBR(
            const std::string& name,
            const core::Color albedo,
            const float metallic,
            const float roughness,
            const float ao) {

           /* MaterialEntry entry = {
                name,
                core::Material(
                    CB_SHADER_LIBRARY.getShader("pbr"),
                )
            };
            materials.push(entry);*/
            return materials.getSize() - 1;
        }

        void MaterialLibrary::init() {
            instance = std::make_unique<MaterialLibrary>();
        }

        MaterialLibrary& MaterialLibrary::getMaterialLibrary() {
            return *instance;
        }
    }
}

#define CB_MATERIAL_LIBRARY ::cobalt::engine::MaterialLibrary::getMaterialLibrary()