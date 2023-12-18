//
// Created by tomas on 18-12-2023.
//

#pragma once

#include "core/gl/texture.h"
#include "core/gl/shader.h"
#include "core/gl/vao.h"
#include "core/gl/ibo.h"


namespace cobalt {
    namespace core {
        class Skybox {
            public:
            /* Destroys the skybox.
             */
            ~Skybox() = default;

            /* Copy constructor.
             * @param other: The other skybox.
             * @return: The copied skybox.
             */
            Skybox(const Skybox& other) = delete;
            /* Move constructor.
             * @param other: The other skybox.
             * @return: The moved skybox.
             */
            Skybox(Skybox&& other) noexcept;
            /* Copy assignment operator.
             * @param other: The other skybox.
             * @return: The copied skybox.
             */
            Skybox& operator=(const Skybox& other) = delete;
            /* Move assignment operator.
             * @param other: The other skybox.
             * @return: The moved skybox.
             */
            Skybox& operator=(Skybox&& other) = delete;

            /* Creates a new skybox.
             * @param texture: The texture of the skybox.
             * @param shader: The shader to render it with.
             * @return: The skybox.
             */
            static Skybox create(const Texture3D& texture, Shader& shader);
            
            /* Binds the skybox.
             */
            void bind() const;
            /* Renders the skybox.
             */
            void render() const;

            /* Gets the texture.
             * @return: The texture.
             */
            const Texture3D& getTexture() const;
            /* Gets the shader.
             * @return: The shader.
             */
            Shader& getShader() const;

            private:
            VAO vao;                    // The vertex array object for the skybox cube.
            IBO ibo;                    // The index buffer object.
            const Texture3D& texture;   // The texture.
            Shader& shader;             // The shader.

            /* Creates a new skybox.
             * @param texture: The texture.
             * @param shader: The shader.
             * @param vao: The vertex array object.
             * @param ibo: The index buffer object.
             * @return: The skybox.
             */
            Skybox(const Texture3D& texture, Shader& shader, VAO&& vao, IBO&& ibo);
        };
    }
}