/**
 * @file plugin.cpp
 * @brief Plugin for loading 3D meshes.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#include "engine/mesh3d/plugin.h"

#include "engine/material/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Mesh3DPlugin::Mesh3DPlugin() noexcept : core::ecs::Plugin(TITLE, "Provides 3D mesh support.", MaterialPlugin{}) {}

        void Mesh3DPlugin::onPlug(core::ecs::World& world) const noexcept {}

        Mesh Mesh3DPlugin::createRectangle(const uint width, const uint height, Material& material) {
            const float w = width / 2.0f;
            const float h = height / 2.0f;

            const float vertices[] = {// Position, texture coordinates, normal.
                                      -w, -h, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, w,  -h, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                      w,  h,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -w, h,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 32);

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3, false);  // Position.
            layout.push(gl::Type::Float, 2, false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3, false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromQuads(gl::Usage::StaticDraw, 1), material);
        }

        Mesh Mesh3DPlugin::createSphere(const uint radius, Material& material) {
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
            layout.push(gl::Type::Float, 3, false);  // Position.
            layout.push(gl::Type::Float, 2, false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3, false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO(gl::Usage::StaticDraw, indices, 6 * stacks * slices), material);
        }

        Mesh Mesh3DPlugin::createCube(const uint size, Material& material) {
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
            layout.push(gl::Type::Float, 3, false);  // Position.
            layout.push(gl::Type::Float, 2, false);  // Texture coordinates.
            layout.push(gl::Type::Float, 3, false);  // Normal.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromQuads(gl::Usage::StaticDraw, 6), material);
        }

        Mesh Mesh3DPlugin::createGrid(const uint size, Material& material) {
            const float s = size / 2.0f;
            const float vertices[] = {
                // Position, texture coordinates
                -s, 0.0f, -s, 0.0f, 0.0f, s, 0.0f, -s, 1.0f, 0.0f, s, 0.0f, s, 1.0f, 1.0f, -s, 0.0f, s, 0.0f, 1.0f,
            };

            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 20);

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3, false);  // Position.
            layout.push(gl::Type::Float, 2, false);  // Texture coordinates.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromQuads(gl::Usage::StaticDraw, 1), material);
        }

        Mesh Mesh3DPlugin::createSkybox(Material& material) {
            const float vertices[24] = {
                -1.0f, -1.0f, 1.0f,   // 0
                1.0f,  -1.0f, 1.0f,   // 1
                1.0f,  1.0f,  1.0f,   // 2
                -1.0f, 1.0f,  1.0f,   // 3
                -1.0f, -1.0f, -1.0f,  // 4
                1.0f,  -1.0f, -1.0f,  // 5
                1.0f,  1.0f,  -1.0f,  // 6
                -1.0f, 1.0f,  -1.0f   // 7
            };
            gl::VBO vbo(gl::Usage::StaticDraw);
            vbo.bind();
            vbo.load(vertices, sizeof(float) * 24);

            gl::VAOLayout layout;
            layout.push(gl::Type::Float, 3, false);  // Position.
            return Mesh(gl::VAO(vbo, layout), gl::IBO::fromCube(gl::Usage::StaticDraw), material);
        }
    }  // namespace engine
}  // namespace cobalt