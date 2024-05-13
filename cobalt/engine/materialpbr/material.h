// Created by tomas on
// 06-12-2023

#pragma once

#include "core/ecs/component/component.h"
#include "core/gl/shader.h"
#include "core/gl/texture.h"

namespace cobalt {
    namespace engine {
        class MaterialPBR : public core::ecs::Component {
            friend class MaterialFactory;

            public:
            /**
             * @brief Default destructor.
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
            MaterialPBR(MaterialPBR&& other) noexcept;

            /**
             * @brief Get the shader for this material.
             * @return The shader.
             */
            core::gl::Shader& getShader() noexcept;
            /**
             * @brief Get an immutable reference to the textures.
             * @return The textures.
             */
            const UMap<std::string, const core::gl::Texture&>& getTextures() const noexcept;

            private:
            /**
             * @brief Creates a new material.
             * @param shader The shader program.
             * @param textures The textures.
             */
            MaterialPBR(core::gl::Shader& shader, const UMap<std::string, const core::gl::Texture&>& textures) noexcept;

            protected:
            core::gl::Shader& shader;                              // Shader program.
            UMap<std::string, const core::gl::Texture&> textures;  // Textures.
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
            static MaterialPBR createMaterialPBR(core::gl::Shader& shader, const core::gl::Texture& albedo, const core::gl::Texture& normal,
                                                 const core::gl::Texture& mrao) noexcept;

            /**
             * @brief Create a new unlit material.
             * @param shader The shader program.
             * @param color The color texture.
             * @return The material.
             */
            static MaterialPBR createMaterialUnlit(core::gl::Shader& shader, const core::gl::Texture& color) noexcept;

            /**
             * @brief Create a new material from the given shader.
             * @param shader The shader program.
             * @param textures The uniform textures of the material.
             * @return The material.
             */
            static MaterialPBR createMaterial(core::gl::Shader& shader, const UMap<std::string, const core::gl::Texture&>& textures) noexcept;
        };
    }  // namespace engine
}  // namespace cobalt