// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/shader.h"
#include "core/gl/texture.h"

namespace cobalt {
    namespace core::gfx {
        class Material {
            friend class MaterialFactory;

            public:
            /**
             * @brief: Destroys the material.
             * @return: void
             */
            virtual ~Material() noexcept = default;
            /**
             * @brief: Copy constructor.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material(const Material& other) noexcept;
            /**
             * @brief: Move constructor.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material(Material&& other) noexcept = delete;
            /**
             * @brief: Copy assignment operator.
             * @param other: The other material.
             * @return: The copied material.
             */
            Material& operator=(const Material& other) noexcept = delete;
            /**
             * @brief: Move assignment operator.
             * @param other: The other material.
             * @return: The moved material.
             */
            Material& operator=(Material&& other) noexcept = delete;

            /**
             * @brief: Get the shader for this material.
             * @return: The shader.
             */
            gl::Shader& getShader() noexcept;
            /**
             * @brief: Get an immutable reference to the textures.
             * @return: The textures.
             */
            const UMap<std::string, const gl::Texture&>& getTextures() const noexcept;

            private:
            /**
             * @brief: Creates a new material.
             * @param shader: The shader program.
             * @param textures: The textures.
             * @return: The material.
             */
            Material(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept;

            protected:
            gl::Shader& shader;                                    // Shader program.
            const UMap<std::string, const gl::Texture&> textures;  // Textures.
        };

        class MaterialFactory {
            public:
            /**
             * @brief: Create a new PBR material.
             * @param shader: The shader program.
             * @param albedo: The albedo texture.
             * @param normal: The normal texture.
             * @param mrao: The mrao texture.
             * @return: The material.
             */
            static Material createMaterialPBR(gl::Shader& shader, const gl::Texture& albedo, const gl::Texture& normal,
                                              const gl::Texture& mrao) noexcept;

            /**
             * @brief: Create a new unlit material.
             * @param shader: The shader program.
             * @param color: The color texture.
             * @return: The material.
             */
            static Material createMaterialUnlit(gl::Shader& shader, const gl::Texture& color) noexcept;

            /**
             * @brief: Create a new material from the given shader.
             * @param shader: The shader program.
             * @param textures: The uniform textures of the material.
             * @return: The material.
             */
            static Material createMaterial(gl::Shader& shader, const UMap<std::string, const gl::Texture&>& textures) noexcept;
        };
    }  // namespace core::gfx
}  // namespace cobalt