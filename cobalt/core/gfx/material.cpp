//
// Created by tomas on 06-12-2023.
//

#include "core/gfx/material.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        Material::Material(
            Shader& shader,
            const Texture& colorMap,
            const Texture& normalMap,
            const Texture& specularMap) :
            shader(shader),
            colorMap(colorMap),
            normalMap(normalMap),
            specularMap(specularMap) {
            CB_CORE_WARN("Material created");
        }

        Material::~Material() {
            CB_CORE_WARN("Material destroyed");
        }

        Material::Material(const Material& other) :
            shader(other.shader),
            colorMap(other.colorMap),
            normalMap(other.normalMap),
            specularMap(other.specularMap) {
            CB_CORE_WARN("Material copied");
        }

        Material::Material(Material&& other) noexcept :
            shader(other.shader),
            colorMap(other.colorMap),
            normalMap(other.normalMap),
            specularMap(other.specularMap) {
            CB_CORE_WARN("Material moved");
        }

        const Material::Uniform Material::getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const {
            colorMap.bindToUnit(colorSlot);
            normalMap.bindToUnit(normalSlot);
            specularMap.bindToUnit(specularSlot);
            return {colorSlot, normalSlot, specularSlot};
        }

        void Material::bind() const {
            // TODO: set material uniforms.
        }

        Shader& Material::getShader() {
            return shader;
        }
    }
}