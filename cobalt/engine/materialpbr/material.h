// Created by tomas on
// 06-12-2023

#pragma once

#include "core/ecs/component/component.h"
#include "core/gl/shader.h"
#include "core/gl/texture.h"

namespace cobalt {
    namespace core::gfx {
        class MaterialPBR : public core::ecs::Component {
            friend class MaterialFactory;

            public:
            /**
             * @brief Destroys the material.
             */
            virtual ~MaterialPBR() noexcept = default;
            /**
             * @brief Copy constructor.
             * @param other The other material.
             * @return The copied material.
             */
            MaterialPBR(const MaterialPBR& other) noexcept;
            /**
             * @brief Move constructor.
             * @param other The other material.
             * @return The moved material.
             */
            MaterialPBR(MaterialPBR&& other) noexcept = delete;
            /**
             * @brief Copy assignment operator.
             * @param other The other material.
             * @return The copied material.
             */
            MaterialPBR& operator=(const MaterialPBR& other) noexcept = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other material.
             * @return The moved material.
             */
            MaterialPBR& operator=(MaterialPBR&& other) noexcept = delete;

            /**
             * @brief Get the shader for this material.
             * @return The shader.
             */
            gl::Shader& getShader() noexcept;
            /**
             * @brief Get an immutable reference to the textures.
             * @return The textures.
             */
            const UMap<std::string, const gl::Texture&>& getTextures() const noexcept;

            private:
            /**
             * @brief Creates a new material.
             * @param shader The shader program.
             * @param textures The textures.
             */
            MaterialPBR(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept;
            /**
             * @brief Creates a new material.
             */
            MaterialPBR() noexcept;

            protected:
            gl::Shader& shader;                                    // Shader program.
            const UMap<std::string, const gl::Texture&> textures;  // Textures.
        };

        class MaterialFactory {
            public:
            /**
             * @brief Create a new PBR material.
             * @param shader The shader program.
             * @param albedo The albedo texture.
             * @param normal The normal texture.
             * @param mrao The mrao texture.
             * @return The material.
             */
            static MaterialPBR createMaterialPBR(gl::Shader& shader, const gl::Texture& albedo, const gl::Texture& normal,
                                                 const gl::Texture& mrao) noexcept;

            /**
             * @brief Create a new unlit material.
             * @param shader The shader program.
             * @param color The color texture.
             * @return The material.
             */
            static MaterialPBR createMaterialUnlit(gl::Shader& shader, const gl::Texture& color) noexcept;

            /**
             * @brief Create a new material from the given shader.
             * @param shader The shader program.
             * @param textures The uniform textures of the material.
             * @return The material.
             */
            static MaterialPBR createMaterial(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept;
        };
    }  // namespace core::gfx
}  // namespace cobalt