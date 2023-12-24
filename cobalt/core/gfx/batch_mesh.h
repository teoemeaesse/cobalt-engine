//
// Created by tomas on 23-12-2023.
//

#pragma once

#include "core/pch.h"


namespace cobalt {
    namespace core {
        class BatchMesh {
            public:
            /** Push the vertices and indices of the mesh into the buffers.
             * @param vertices: The buffer to push the vertices into.
             * @param indices: The buffer to push the indices into.
             */
            virtual void pushInto(Buffer& vertices, Buffer& indices) const;

            private:
            glm::vec3 worldTranslate;   // The world translation of the mesh.
            glm::vec3 worldRotate;      // The world rotation of the mesh.
            glm::vec3 worldScale;       // The world scale of the mesh.

            /** Create a batch mesh.
             * @return: The batch mesh.
             */
            BatchMesh() = default;
            /** Destroy the batch mesh.
             */
            ~BatchMesh() = default;
        };

        class BatchQuad : public BatchMesh {
            public:
            /** Push the vertices and indices of the mesh into the buffers.
             * @param vertices: The buffer to push the vertices into.
             * @param indices: The buffer to push the indices into.
             */
            void pushInto(Buffer& vertices, Buffer& indices) const override;
        };

        class BatchSphere : public BatchMesh {
            public:
            /** Push the vertices and indices of the mesh into the buffers.
             * @param vertices: The buffer to push the vertices into.
             * @param indices: The buffer to push the indices into.
             */
            void pushInto(Buffer& vertices, Buffer& indices) const override;
        };
    }
}