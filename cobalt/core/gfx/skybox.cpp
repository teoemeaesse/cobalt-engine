//
// Created
// by
// tomas
// on
// 18-12-2023.
//

#include "core/gfx/skybox.h"

namespace cobalt {
    namespace core {
        Skybox::Skybox(const Texture3D& texture, Shader& shader, VAO&& vao, IBO&& ibo)
            : texture(texture), shader(shader), vao(std::move(vao)), ibo(std::move(ibo)) {}

        Skybox::Skybox(Skybox&& other) noexcept
            : texture(other.texture), shader(other.shader), vao(std::move(other.vao)), ibo(std::move(other.ibo)) {}

        Skybox Skybox::create(const Texture3D& texture, Shader& shader) {
            const float vertices[24] = {
                -1.0f, -1.0f,
                1.0f,  // 0
                1.0f,  -1.0f,
                1.0f,  // 1
                1.0f,  1.0f,
                1.0f,  // 2
                -1.0f, 1.0f,
                1.0f,  // 3
                -1.0f, -1.0f,
                -1.0f,  // 4
                1.0f,  -1.0f,
                -1.0f,  // 5
                1.0f,  1.0f,
                -1.0f,  // 6
                -1.0f, 1.0f,
                -1.0f  // 7
            };
            VBO vbo(GL::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 24);

            VAOLayout layout;
            layout.push(GL::Type::Float, 3,
                        false);  // Position.
            return Skybox(texture, shader, VAO(vbo, layout), IBO::fromCube(GL::Usage::StaticDraw));
        }

        void Skybox::bind() const {
            vao.bind();
            ibo.bind();
            shader.use();
        }

        void Skybox::render() const { glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr); }

        const Texture3D& Skybox::getTexture() const { return texture; }

        Shader& Skybox::getShader() const { return shader; }
    }  // namespace core
}  // namespace
   // cobalt