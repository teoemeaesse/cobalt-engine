// Created by tomas on
// 18-12-2023

#pragma once

#include "core/gl/ibo.h"
#include "core/gl/shader.h"
#include "core/gl/texture.h"
#include "core/gl/vao.h"

namespace cobalt {
    namespace engine {
        class Skybox {
            public:
            /**
             * @brief Destroys the skybox.
             */
            ~Skybox() = default;

            /**
             * @brief Copy constructor.
             * @param other The other skybox.
             * @return The copied skybox.
             */
            Skybox(const Skybox& other) = delete;
            /**
             * @brief Move constructor.
             * @param other The other skybox.
             * @return The moved skybox.
             */
            Skybox(Skybox&& other) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The other skybox.
             * @return The copied skybox.
             */
            Skybox& operator=(const Skybox& other) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other skybox.
             * @return The moved skybox.
             */
            Skybox& operator=(Skybox&& other) = delete;

            /**
             * @brief Creates a new skybox.
             * @param texture The texture of the skybox.
             * @param shader The shader to render it with.
             * @return The skybox.
             */
            static Skybox create(const core::gl::Texture3D& texture, core::gl::Shader& shader);

            /**
             * @brief Binds the skybox.
             */
            void bind() const;
            /**
             * @brief Renders the skybox.
             */
            void render() const;

            /**
             * @brief Gets the texture.
             * @return The texture.
             */
            const core::gl::Texture3D& getTexture() const;
            /**
             * @brief Gets the shader.
             * @return The shader.
             */
            core::gl::Shader& getShader() const;

            private:
            core::gl::VAO vao;                   // The vertex array object for the skybox cube.
            core::gl::IBO ibo;                   // The index buffer object.
            const core::gl::Texture3D& texture;  // The texture.
            core::gl::Shader& shader;            // The shader.

            /**
             * @brief Creates a new skybox.
             * @param texture The texture.
             * @param shader The shader.
             * @param vao The vertex array object.
             * @param ibo The index buffer object.
             * @return The skybox.
             */
            Skybox(const core::gl::Texture3D& texture, core::gl::Shader& shader, core::gl::VAO&& vao, core::gl::IBO&& ibo);
        };
    }  // namespace engine
}  // namespace cobalt