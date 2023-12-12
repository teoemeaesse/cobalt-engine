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
            };

            /* Creates a new material.
             * @param shader: The shader program.
             * @param colorMap: The color map.
             * @param normalMap: The normal map.
             * @param specularMap: The specular map.
             * @return: The material.
             */
            Material(Shader& shader, const Texture& colorMap, const Texture& normalMap, const Texture& specularMap);
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

            /* Returns the uniform for this material.
             * @param colorSlot: The color slot.
             * @param normalSlot: The normal slot.
             * @param specularSlot: The specular slot.
             * @return: The uniform.
             */
            const Uniform getUniform(const int colorSlot, const int normalSlot, const int specularSlot) const;

            /* Binds the material.
             */
            void bind() const;

            /* Get the shader for this material.
             * @return: The shader.
             */
            Shader& getShader();

            protected:
            Shader& shader;             // Shader program.
            const Texture& colorMap;    // Color map.
            const Texture& normalMap;   // Normal map.
            const Texture& specularMap; // Specular map.
        };
    }
}