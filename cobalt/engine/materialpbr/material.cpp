// Created by tomas on
// 06-12-2023

#include "engine/materialpbr/material.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        MaterialPBR::MaterialPBR(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept
            : shader(shader), textures(textures) {}

        MaterialPBR::MaterialPBR(const MaterialPBR& other) noexcept : shader(other.shader), textures(other.textures) {}

        MaterialPBR::MaterialPBR(MaterialPBR&& other) noexcept : shader(other.shader), textures(std::move(other.textures)) {}

        gl::Shader& MaterialPBR::getShader() noexcept { return shader; }

        const UMap<std::string, const gl::Texture&>& MaterialPBR::getTextures() const noexcept { return textures; }

        MaterialPBR MaterialFactory::createMaterialPBR(gl::Shader& shader, const gl::Texture& albedo, const gl::Texture& normal,
                                                       const gl::Texture& mrao) noexcept {
            UMap<std::string, const gl::Texture&> textures;
            textures.emplace("albedo", albedo);
            textures.emplace("normal", normal);
            textures.emplace("mrao", mrao);
            return MaterialPBR(shader, textures);
        }

        MaterialPBR MaterialFactory::createMaterialUnlit(gl::Shader& shader, const gl::Texture& color) noexcept {
            UMap<std::string, const gl::Texture&> textures;
            textures.emplace("color", color);
            return MaterialPBR(shader, textures);
        }

        MaterialPBR MaterialFactory::createMaterial(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept {
            return MaterialPBR(shader, textures);
        }
    }  // namespace engine
}  // namespace cobalt