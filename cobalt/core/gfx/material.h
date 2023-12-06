//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/gl/definitions.h"
#include "core/gl/texture.h"
#include "core/gl/shader.h"
#include "core/gfx/color.h"


namespace cobalt {
    namespace core {
        class Material {
            public:
            struct Uniform {
                const int colorSlot;    // Color slot.
                const int normalSlot;   // Normal slot.
                const int specularSlot; // Specular slot.
                const float shininess;  // Shininess.
            };

            /* Destroys the material.
             */
            ~Material() = default;

            /* Returns the uniform for this material.
             * @param colorSlot: The color slot.
             * @param normalSlot: The normal slot.
             * @param specularSlot: The specular slot.
             * @return: The uniform.
             */
            const Uniform getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const;

            protected:
            const Shader shader;        // Shader program.
            const Texture colorMap;     // Color map.
            const Texture normalMap;    // Normal map.
            const Texture specularMap;  // Specular map.
            const float shininess;      // Shininess.

            /* Creates a new material.
             * @param shader: The shader program.
             * @param colorMap: The color map.
             * @param normalMap: The normal map.
             * @param specularMap: The specular map.
             * @param shininess: The shininess.
             * @return: The material.
             */
            Material(const Shader shader, const Texture colorMap, const Texture normalMap, const Texture specularMap, const float shininess);
        };
    }
}