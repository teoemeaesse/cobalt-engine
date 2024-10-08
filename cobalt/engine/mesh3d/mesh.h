// Created by tomas on
// 08-12-2023

#pragma once

#include "core/ecs/component/component.h"
#include "core/gl/ibo.h"
#include "core/gl/vao.h"
#include "engine/material/material.h"

namespace cobalt {
    namespace engine {
        class Mesh3DPlugin;

        class Mesh : public core::ecs::Component {
            friend class Mesh3DPlugin;

            public:
            /**
             * @brief Destroy the mesh.
             */
            ~Mesh() = default;
            /**
             * @brief Copy constructor.
             * @param other The other mesh.
             */
            Mesh(const Mesh& other) = delete;
            /**
             * @brief Move constructor.
             * @param other The other mesh.
             */
            Mesh(Mesh&& other) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The other mesh.
             * @return The mesh.
             */
            Mesh& operator=(const Mesh& other) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The other mesh.
             * @return The mesh.
             */
            Mesh& operator=(Mesh&& other) = delete;

            /**
             * @brief Offset the mesh world position by a translation vector.
             * @param translation Translation vector.
             */
            void translate(const glm::vec3& translation);
            /**
             * @brief Rotate the mesh around the world axes by a rotation vector (degrees).
             * @param rotation Rotation vector (degrees).
             */
            void rotate(const glm::vec3& rotation);
            /**
             * @brief Scale the mesh by a scale vector.
             * @param scale Scale vector.
             */
            void scale(const glm::vec3& scale);

            /**
             * @brief Get the mesh model matrix.
             * @return The model matrix.
             */
            glm::mat4x4 getModelMatrix() const;

            /**
             * @brief Bind the mesh.
             */
            void bind() const;
            /**
             * @brief Render the mesh.
             */
            void render() const;
            /**
             * @brief Get the mesh material.
             * @return The material.
             */
            Material& getMaterial();
            /**
             * @brief Get the mesh primitive type.
             * @return The primitive type.
             */
            core::gl::Primitive getPrimitive() const;

            private:
            /**
             * @brief Create a mesh.
             * @param vao Vertex array object.
             * @param ibo Index buffer object.
             * @param material Material.
             * @param primitives Primitive type.
             * @return The mesh.
             */
            Mesh(core::gl::VAO&& vao, core::gl::IBO&& ibo, Material& material, const core::gl::Primitive& primitive = core::gl::Primitive::Triangles);

            core::gl::VAO vao;              // Vertex array object.
            core::gl::IBO ibo;              // Index buffer object.
            core::gl::Primitive primitive;  // Primitive type.
            Material& material;             // Material.
            glm::vec3 worldTranslate;       // World position.
            glm::vec3 worldRotate;          // World rotation (degrees).
            glm::vec3 worldScale;           // World scale.
        };
    }  // namespace engine
}  // namespace cobalt