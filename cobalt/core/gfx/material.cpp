//
// Created by tomas on 06-12-2023.
//

#include "core/gfx/material.h"


namespace cobalt {
    namespace core {
        Material::Material(
            Shader& shader,
            const Texture& albedoMap,
            const Texture& normalMap,
            const Texture& mraoMap) :
            shader(shader),
            albedoMap(albedoMap),
            normalMap(normalMap),
            mraoMap(mraoMap) {
        }

        Material::Material(const Material& other) :
            shader(other.shader),
            albedoMap(other.albedoMap),
            normalMap(other.normalMap),
            mraoMap(other.mraoMap) {
        }

        bool Material::operator==(const Material& other) const {
            return shader.getGLHandle() == other.shader.getGLHandle() &&
                   albedoMap.getGLHandle() == other.albedoMap.getGLHandle() &&
                   normalMap.getGLHandle() == other.normalMap.getGLHandle() &&
                   mraoMap.getGLHandle() == other.mraoMap.getGLHandle();
        }

        const Material::Uniform Material::getUniform(const int albedoSlot, const int normalSlot, const int mraoSlot) const {
            albedoMap.bindToUnit(albedoSlot);
            normalMap.bindToUnit(normalSlot);
            mraoMap.bindToUnit(mraoSlot);
            return {albedoSlot, normalSlot, mraoSlot};
        }

        const Texture& Material::getAlbedoMap() const {
            return albedoMap;
        }

        const Texture& Material::getNormalMap() const {
            return normalMap;
        }

        const Texture& Material::getMRAOMap() const {
            return mraoMap;
        }

        Shader& Material::getShader() {
            return shader;
        }
    }
}