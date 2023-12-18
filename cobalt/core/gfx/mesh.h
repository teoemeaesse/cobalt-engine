//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gl/vao.h"
#include "core/gl/ibo.h"
#include "core/gfx/material.h"


namespace cobalt {
    namespace core {
        class Mesh {
            public:
            /* Create a mesh.
             * @param vao: Vertex array object.
             * @param ibo: Index buffer object.
             * @param material: Material.
             * @param primitives: Primitive type.
             * @return: The mesh.
             */
            Mesh(VAO&& vao,
                 IBO&& ibo,
                 Material* material,
                 const GLPrimitive& primitive = GLPrimitive::Triangles);
            /* Destroy the mesh.
             */
            ~Mesh() = default;
            /* Copy constructor.
             * @param other: The other mesh.
             */
            Mesh(const Mesh& other) = delete;
            /* Move constructor.
             * @param other: The other mesh.
             */
            Mesh(Mesh&& other) noexcept;
            /* Copy assignment operator.
             * @param other: The other mesh.
             * @return: The mesh.
             */
            Mesh& operator=(const Mesh& other) = delete;
            /* Move assignment operator.
             * @param other: The other mesh.
             * @return: The mesh.
             */
            Mesh& operator=(Mesh&& other) noexcept;

            /* Offset the mesh world position by a translation vector.
             * @param translation: Translation vector.
             */
            void translate(const glm::vec3& translation);
            /* Rotate the mesh around the world axes by a rotation vector (degrees).
             * @param rotation: Rotation vector (degrees).
             */
            void rotate(const glm::vec3& rotation);
            /* Scale the mesh by a scale vector.
             * @param scale: Scale vector.
             */
            void scale(const glm::vec3& scale);

            /* Get the mesh model matrix.
             * @return: The model matrix.
             */
            glm::mat4x4 getModelMatrix() const;

            /* Bind the mesh.
             */
            void bind() const;
            /* Render the mesh.
             */
            void render() const;
            /* Get the mesh material.
             * @return: The material.
             */
            Material& getMaterial();
            /* Get the mesh primitive type.
             * @return: The primitive type.
             */
            GLPrimitive getPrimitive() const;

            /* Create a rectangle-shaped mesh.
             * @param width: The width.
             * @param height: The height.
             * @param material: The material.
             * @return: The rectangle mesh.
             */
            static Mesh createRectangle(const uint width, const uint height, Material* material);

            /* Create a circle-shaped mesh.
             * @param radius: The radius.
             * @param material: The material.
             * @return: The circle mesh.
             */

            static Mesh createSphere(const uint radius, Material* material);

            private:
            VAO vao;                    // Vertex array object.
            IBO ibo;                    // Index buffer object.
            Material* material;         // Material.
            GLPrimitive primitive;      // Primitive type.
            glm::vec3 worldTranslate;   // World position.
            glm::vec3 worldRotate;      // World rotation (degrees).
            glm::vec3 worldScale;       // World scale.
        };
    }
}