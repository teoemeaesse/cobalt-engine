// Created by tomas on
// 23-12-2023

#pragma once

// #include "core/pch.h"

// namespace cobalt {
//     namespace core::gfx {
//         class BatchMesh {
//             public:
//             /**
//              * @brief: Push the vertices and indices of the mesh into the buffers.
//              * @param vertices: The buffer to push the vertices into.
//              * @param indices: The buffer to push the indices into.
//              * @return: void
//              */
//             virtual void pushInto(Vec<char>& vertices, Vec<char>& indices) const;

//             private:
//             glm::vec3 worldTranslate;  // The world translation of the mesh.
//             glm::vec3 worldRotate;     // The world rotation of the mesh.
//             glm::vec3 worldScale;      // The world scale of the mesh.

//             /**
//              * @brief: Create a batch mesh.
//              * @return: The batch mesh.
//              */
//             BatchMesh() = default;
//             /**
//              * @brief: Destroy the batch mesh.
//              */
//             ~BatchMesh() = default;
//         };

//         class BatchQuad : public BatchMesh {
//             public:
//             /**
//              * @brief: Push the vertices and indices of the mesh into the buffers.
//              * @param vertices: The buffer to push the vertices into.
//              * @param indices: The buffer to push the indices into.
//              * @return: void
//              */
//             void pushInto(Vec<char>& vertices, Vec<char>& indices) const override;
//         };

//         class BatchSphere : public BatchMesh {
//             public:
//             /**
//              * @brief: Push the vertices and indices of the mesh into the buffers.
//              * @param vertices: The buffer to push the vertices into.
//              * @param indices: The buffer to push the indices into.
//              * @return: void
//              */
//             void pushInto(Vec<char>& vertices, Vec<char>& indices) const override;
//         };
//     }  // namespace core::gfx
// }  // namespace cobalt