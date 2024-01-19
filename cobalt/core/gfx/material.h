// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/shader.h"
#include "core/gl/texture.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
        class Material {
            public:
            struct Uniform {
                const int albedoSlot;  // Surface albedo slot.
                const int normalSlot;  // Surface normal slot.
                const int mraoSlot;    // Metallic (R), roughness (G) and AO (B) slot.
            };

            /** @brief: Creates a new material.
             * @param shader: The shader program.
             * @param albedoMap: The surface albedo map.
             * @param normalMap: The surface normal map.
             * @param mraoMap: The metallic (R), roughness (G) and AO (B) map.
             * @return: The material.
             */
            Material(gl::Shader& shader, const gl::Texture& albedoMap, const gl::Texture& normalMap, const gl::Texture& mraoMap);
            /** @brief: Destroys the material.
             */
            ~Material() = default;
            /** @brief: Copy constructor.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material(const Material& other);
            /** @brief: Move constructor.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material(Material&& other) noexcept = delete;
            /** @brief: Copy assignment operator.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material& operator=(const Material& other) = delete;
            /** @brief: Move assignment operator.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material& operator=(Material&& other) noexcept = delete;
            /** @brief: Equality operator.
             * @param other: The other material.
             * @return: True if the materials are equal, false otherwise.
             */
            bool operator==(const Material& other) const;

            /** @brief: Returns the uniform for this material.
             * @param colorSlot: The color slot.
             * @param normalSlot: The normal slot.
             * @param specularSlot: The specular slot.
             * @return: The uniform.
             */
            const Uniform getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const;
            /** @brief: Get the albedo map.
             * @return: The albedo map.
             */
            const gl::Texture& getAlbedoMap() const;
            /** @brief: Get the normal map.
             * @return: The normal map.
             */
            const gl::Texture& getNormalMap() const;
            /** @brief: Get the metallic (R), roughness (G) and AO (B) map.
             * @return: The metallic (R), roughness (G) and AO (B) map.
             */
            const gl::Texture& getMRAOMap() const;

            /** @brief: Get the shader for this material.
             * @return: The shader.
             */
            gl::Shader& getShader();

            protected:
            gl::Shader& shader;            // Shader program.
            const gl::Texture& albedoMap;  // Surface albedo map.
            const gl::Texture& normalMap;  // Surface normal map.
            const gl::Texture& mraoMap;    // Metallic (R), roughness (G) and AO (B) map.
        };
    }  // namespace core::gfx
}  // namespace cobalt