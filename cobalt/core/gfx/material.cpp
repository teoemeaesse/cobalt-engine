//
// Created by tomas on 06-12-2023.
//

#include "core/gfx/material.h"


namespace cobalt {
    namespace core {
        Material::Material(
            const Shader shader,
            const Texture colorMap,
            const Texture normalMap,
            const Texture specularMap,
            const float shininess)
            : shader(shader), colorMap(colorMap), normalMap(normalMap), specularMap(specularMap), shininess(shininess) {
        }

        const Material::Uniform Material::getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const {
            colorMap.bindToUnit(colorSlot);
            normalMap.bindToUnit(normalSlot);
            specularMap.bindToUnit(specularSlot);
            return {colorSlot, normalSlot, specularSlot, shininess};
        }
    }
}