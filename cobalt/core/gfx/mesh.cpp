// Created by tomas on
// 08-12-2023

#include "core/gfx/mesh.h"

#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
        Mesh::Mesh(gl::VAO&& vao, gl::IBO&& ibo, Material& material, const gl::Primitive& primitive)
            : vao(std::move(vao)),
              ibo(std::move(ibo)),
              material(material),
              primitive(primitive),
              worldTranslate(0.0f),
              worldRotate(0.0f),
              worldScale(1.0f) {}

        Mesh::Mesh(Mesh&& other) noexcept
            : vao(std::move(other.vao)),
              ibo(std::move(other.ibo)),
              material(other.material),
              primitive(other.primitive),
              worldTranslate(other.worldTranslate),
              worldRotate(other.worldRotate),
              worldScale(other.worldScale) {}

        void Mesh::translate(const glm::vec3& translation) { this->worldTranslate += translation; }

        void Mesh::rotate(const glm::vec3& rotation) { this->worldRotate += rotation; }

        void Mesh::scale(const glm::vec3& scale) { this->worldScale *= scale; }

        glm::mat4x4 Mesh::getModelMatrix() const {
            const glm::vec3 rotation = glm::radians(this->worldRotate);
            const float cx = cos(rotation.x);
            const float sx = sin(rotation.x);
            const float cy = cos(rotation.y);
            const float sy = sin(rotation.y);
            const float cz = cos(rotation.z);
            const float sz = sin(rotation.z);

            return {worldScale.x * cz * cy,
                    worldScale.x * (cz * sy * sx - cx * sz),
                    worldScale.x * (cx * cz * sy + sx * sz),
                    0.0f,
                    worldScale.y * sz * cy,
                    worldScale.y * (sx * sy * sz + cx * cz),
                    worldScale.y * (cx * sy * sz - cz * sx),
                    0.0f,
                    -worldScale.z * sy,
                    worldScale.z * cy * sx,
                    worldScale.z * cx * cy,
                    0.0f,
                    worldTranslate.x,
                    worldTranslate.y,
                    worldTranslate.z,
                    1.0f};
        }

        void Mesh::bind() const {
            this->vao.bind();
            this->ibo.bind();
            this->material.getShader().use();
        }

        void Mesh::render() const { glDrawElements((GLenum)this->primitive, this->ibo.getCount(), GL_UNSIGNED_INT, nullptr); }

        Material& Mesh::getMaterial() { return this->material; }

        Mesh Mesh::createRectangle(const uint width, const uint height, Material& material) {
            const float w = width / 2.0f;
            const float h = height / 2.0f;

            const float vertices[] = {// Position, texture coordinates, normal.
                                      -w, -h, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, w,  -h, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                      w,  h,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -w, h,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 32);

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3,
                        false);  // Position.
            layout.push(gl::Type::Float, 2,
                        false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3,
                        false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromQuads(gl::Usage::StaticDraw, 1), material);
        }

        Mesh Mesh::createSphere(const uint radius, Material& material) {
            const uint stacks = 20;
            const uint slices = 20;

            const float stackStep = M_PI / stacks;
            const float sliceStep = 2.0f * M_PI / slices;

            float vertices[8 * (stacks + 1) * (slices + 1)];
            uint indices[6 * stacks * slices];

            for (uint i = 0; i <= stacks; i++) {
                const float stackAngle = M_PI / 2.0f - i * stackStep;
                const float xy = radius * cos(stackAngle);
                const float z = radius * sin(stackAngle);

                for (uint j = 0; j <= slices; j++) {
                    const float sliceAngle = j * sliceStep;
                    const float x = xy * cos(sliceAngle);
                    const float y = xy * sin(sliceAngle);

                    vertices[8 * (i * (slices + 1) + j) + 0] = x;
                    vertices[8 * (i * (slices + 1) + j) + 1] = y;
                    vertices[8 * (i * (slices + 1) + j) + 2] = z;
                    vertices[8 * (i * (slices + 1) + j) + 3] = (float)j / slices;
                    vertices[8 * (i * (slices + 1) + j) + 4] = (float)i / stacks;
                    vertices[8 * (i * (slices + 1) + j) + 5] = x / radius;
                    vertices[8 * (i * (slices + 1) + j) + 6] = y / radius;
                    vertices[8 * (i * (slices + 1) + j) + 7] = z / radius;
                }
            }

            for (uint i = 0; i < stacks; i++) {
                for (uint j = 0; j < slices; j++) {
                    indices[6 * (i * slices + j) + 0] = i * (slices + 1) + j;
                    indices[6 * (i * slices + j) + 1] = i * (slices + 1) + j + 1;
                    indices[6 * (i * slices + j) + 2] = (i + 1) * (slices + 1) + j;
                    indices[6 * (i * slices + j) + 3] = i * (slices + 1) + j + 1;
                    indices[6 * (i * slices + j) + 4] = (i + 1) * (slices + 1) + j + 1;
                    indices[6 * (i * slices + j) + 5] = (i + 1) * (slices + 1) + j;
                }
            }

            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 8 * (stacks + 1) * (slices + 1));

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3,
                        false);  // Position.
            layout.push(gl::Type::Float, 2,
                        false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3,
                        false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO(gl::Usage::StaticDraw, indices, 6 * stacks * slices), material);
        }

        Mesh Mesh::createCube(const uint size, Material& material) {
            const float s = size / 2.0f;

            const float vertices[] = {// Position, texture coordinates, normal.
                                      -s, -s, -s, 0.0f, 0.0f, 0.0f,  0.0f,  -1.0f, s,  -s, -s, 1.0f, 0.0f, 0.0f,  0.0f,  -1.0f,
                                      s,  s,  -s, 1.0f, 1.0f, 0.0f,  0.0f,  -1.0f, -s, s,  -s, 0.0f, 1.0f, 0.0f,  0.0f,  -1.0f,

                                      -s, -s, s,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,  s,  -s, s,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
                                      s,  s,  s,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  -s, s,  s,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,

                                      -s, -s, -s, 0.0f, 0.0f, -1.0f, 0.0f,  0.0f,  -s, s,  -s, 1.0f, 0.0f, -1.0f, 0.0f,  0.0f,
                                      -s, s,  s,  1.0f, 1.0f, -1.0f, 0.0f,  0.0f,  -s, -s, s,  0.0f, 1.0f, -1.0f, 0.0f,  0.0f,

                                      s,  -s, -s, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,  s,  s,  -s, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
                                      s,  s,  s,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  s,  -s, s,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,

                                      -s, -s, -s, 0.0f, 0.0f, 0.0f,  -1.0f, 0.0f,  -s, -s, s,  1.0f, 0.0f, 0.0f,  -1.0f, 0.0f,
                                      s,  -s, s,  1.0f, 1.0f, 0.0f,  -1.0f, 0.0f,  s,  -s, -s, 0.0f, 1.0f, 0.0f,  -1.0f, 0.0f,

                                      -s, s,  -s, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,  -s, s,  s,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
                                      s,  s,  s,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  s,  s,  -s, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f};

            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 192);

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3,
                        false);  // Position.
            layout.push(gl::Type::Float, 2,
                        false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3,
                        false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromQuads(gl::Usage::StaticDraw, 6), material);
        }
    }  // namespace core::gfx
}  // namespace cobalt