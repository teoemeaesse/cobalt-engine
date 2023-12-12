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
                 const Material& material,
                 const GLPrimitive& primitive = GLPrimitive::Triangles);
            /* Destroy the mesh.
             */
            ~Mesh() = default;

            /* Offset the mesh world position by a translation vector.
             * @param translation: Translation vector.
             */
            void translate(const glm::vec3& translation);
            /* Rotate the mesh around the world axes by a rotation vector (radians).
             * @param rotation: Rotation vector (radians).
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

            /* Get the mesh vertex array object.
             * @return: The vertex array object.
             */
            VAO& getVAO();
            /* Get the mesh index buffer object.
             * @return: The index buffer object.
             */
            IBO& getIBO();
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
            static Mesh createRectangle(const uint width, const uint height, const Material& material);

            private:
            VAO vao;                    // Vertex array object.
            IBO ibo;                    // Index buffer object.
            Material material;          // Material.
            GLPrimitive primitive;      // Primitive type.
            glm::vec3 worldTranslate;   // World position.
            glm::vec3 worldRotate;      // World rotation (radians).
            glm::vec3 worldScale;       // World scale.
        };
    }
}