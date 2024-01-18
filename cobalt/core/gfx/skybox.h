//
// Created
// by
// tomas
// on
// 18-12-2023.
//

#pragma once

#include "core/gl/ibo.h"
#include "core/gl/shader.h"
#include "core/gl/texture.h"
#include "core/gl/vao.h"

namespace cobalt {
    namespace core {
        class Skybox {
            public:
            /** @brief: Destroys the skybox.
             */
            ~Skybox() = default;

            /** @brief: Copy constructor.
             * @param other: The other skybox.
             * @return: The copied skybox.
             */
            Skybox(const Skybox& other) = delete;
            /** @brief: Move constructor.
             * @param other: The other skybox.
             * @return: The moved skybox.
             */
            Skybox(Skybox&& other) noexcept;
            /** @brief: Copy assignment operator.
             * @param other: The other skybox.
             * @return: The copied skybox.
             */
            Skybox& operator=(const Skybox& other) = delete;
            /** @brief: Move assignment operator.
             * @param other: The other skybox.
             * @return: The moved skybox.
             */
            Skybox& operator=(Skybox&& other) = delete;

            /** @brief: Creates a new skybox.
             * @param texture: The texture of the skybox.
             * @param shader: The shader to render it with.
             * @return: The skybox.
             */
            static Skybox create(const Texture3D& texture, Shader& shader);

            /** @brief: Binds the skybox.
             */
            void bind() const;
            /** @brief: Renders the skybox.
             */
            void render() const;

            /** @brief: Gets the texture.
             * @return: The texture.
             */
            const Texture3D& getTexture() const;
            /** @brief: Gets the shader.
             * @return: The shader.
             */
            Shader& getShader() const;

            private:
            VAO vao;                   // The vertex array object for the skybox cube.
            IBO ibo;                   // The index buffer object.
            const Texture3D& texture;  // The texture.
            Shader& shader;            // The shader.

            /** @brief: Creates a new skybox.
             * @param texture: The texture.
             * @param shader: The shader.
             * @param vao: The vertex array object.
             * @param ibo: The index buffer object.
             * @return: The skybox.
             */
            Skybox(const Texture3D& texture, Shader& shader, VAO&& vao, IBO&& ibo);
        };
    }  // namespace core
}  // namespace
   // cobalt