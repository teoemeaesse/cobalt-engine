// Created by tomas on
// 06-12-2023

#include "core/gfx/material.h"

namespace cobalt {
    namespace core::gfx {
        Material::Material(gl::Shader& shader, const gl::Texture& albedoMap, const gl::Texture& normalMap, const gl::Texture& mraoMap)
            : shader(shader), albedoMap(albedoMap), normalMap(normalMap), mraoMap(mraoMap) {}

        Material::Material(const Material& other)
            : shader(other.shader), albedoMap(other.albedoMap), normalMap(other.normalMap), mraoMap(other.mraoMap) {}

        bool Material::operator==(const Material& other) const {
            return shader.getGLHandle() == other.shader.getGLHandle() && albedoMap.getGLHandle() == other.albedoMap.getGLHandle() &&
                   normalMap.getGLHandle() == other.normalMap.getGLHandle() && mraoMap.getGLHandle() == other.mraoMap.getGLHandle();
        }

        const Material::Uniform Material::getUniform(const int albedoSlot, const int normalSlot, const int mraoSlot) const {
            albedoMap.bindToUnit(albedoSlot);
            normalMap.bindToUnit(normalSlot);
            mraoMap.bindToUnit(mraoSlot);
            return {albedoSlot, normalSlot, mraoSlot};
        }

        const gl::Texture& Material::getAlbedoMap() const { return albedoMap; }

        const gl::Texture& Material::getNormalMap() const { return normalMap; }

        const gl::Texture& Material::getMRAOMap() const { return mraoMap; }

        gl::Shader& Material::getShader() { return shader; }
    }  // namespace core::gfx
}  // namespace cobalt