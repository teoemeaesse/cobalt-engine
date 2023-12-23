//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/pch.h"
#include "core/gl/texture.h"
#include "core/gl/shader.h"


namespace cobalt {
    namespace core {
        class Material {
            public:
            struct Uniform {
                const int albedoSlot;   // Surface albedo slot.
                const int normalSlot;   // Surface normal slot.
                const int mraoSlot;     // Metallic (R), roughness (G) and AO (B) slot.
            };

            /* Creates a new material.
             * @param shader: The shader program.
             * @param albedoMap: The surface albedo map.
             * @param normalMap: The surface normal map.
             * @param mraoMap: The metallic (R), roughness (G) and AO (B) map.
             * @return: The material.
             */
            Material(Shader& shader, const Texture& albedoMap, const Texture& normalMap, const Texture& mraoMap);
            /* Destroys the material.
             */
            ~Material() = default;
            /* Copy constructor.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material(const Material& other);
            /* Move constructor.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material(Material&& other) noexcept;
            /* Copy assignment operator.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material& operator=(const Material& other) = delete;
            /* Move assignment operator.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material& operator=(Material&& other) noexcept = delete;
            /* Equality operator.
             * @param other: The other material.
             * @return: True if the materials are equal, false otherwise.
             */
            bool operator==(const Material& other) const;

            /* Returns the uniform for this material.
             * @param colorSlot: The color slot.
             * @param normalSlot: The normal slot.
             * @param specularSlot: The specular slot.
             * @return: The uniform.
             */
            const Uniform getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const;
            /* Get the albedo map.
             * @return: The albedo map.
             */
            const Texture& getAlbedoMap() const;
            /* Get the normal map.
             * @return: The normal map.
             */
            const Texture& getNormalMap() const;
            /* Get the metallic (R), roughness (G) and AO (B) map.
             * @return: The metallic (R), roughness (G) and AO (B) map.
             */
            const Texture& getMRAOMap() const;

            /* Get the shader for this material.
             * @return: The shader.
             */
            Shader& getShader();

            protected:
            Shader& shader;             // Shader program.
            const Texture& albedoMap;   // Surface albedo map.
            const Texture& normalMap;   // Surface normal map.
            const Texture& mraoMap;     // Metallic (R), roughness (G) and AO (B) map.
        };
    }
}