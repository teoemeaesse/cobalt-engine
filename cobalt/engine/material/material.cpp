// Created by tomas on
// 06-12-2023

#include "engine/material/material.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Material::Material(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept : shader(shader), textures(textures) {}

        Material::Material(const Material& other) noexcept : shader(other.shader), textures(other.textures) {}

        Material::Material(Material&& other) noexcept : shader(other.shader), textures(std::move(other.textures)) {}

        Material& Material::operator=(Material&& other) noexcept {
            shader = Move(other.shader);
            textures = Move(other.textures);
            return *this;
        }

        gl::Shader& Material::getShader() noexcept { return shader; }

        const UMap<std::string, const gl::Texture&>& Material::getTextures() const noexcept { return textures; }

        Material MaterialFactory::createMaterialPBR(gl::Shader& shader, const gl::Texture& albedo, const gl::Texture& normal,
                                                    const gl::Texture& mrao) noexcept {
            UMap<std::string, const gl::Texture&> textures;
            textures.emplace("albedo", albedo);
            textures.emplace("normal", normal);
            textures.emplace("mrao", mrao);
            return Material(shader, textures);
        }

        Material MaterialFactory::createMaterialUnlit(gl::Shader& shader, const gl::Texture& color) noexcept {
            UMap<std::string, const gl::Texture&> textures;
            textures.emplace("color", color);
            return Material(shader, textures);
        }

        Material MaterialFactory::createMaterial(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept {
            return Material(shader, textures);
        }
    }  // namespace engine
}  // namespace cobalt