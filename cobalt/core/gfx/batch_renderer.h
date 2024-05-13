// Created by tomas on
// 23-12-2023

#pragma once

// #include "core/gfx/batch_mesh.h"
// #include "core/pch.h"
// #include "engine/raster3d/renderer.h"

// namespace cobalt {
//     namespace core::gfx {
//         class Batch {
//             public:
//             Batch();
//             ~Batch();

//             /**
//              * @brief Add a mesh to the batch.
//              * @param mesh The mesh to add.
//              */
//             void add(BatchMesh& mesh);

//             private:
//             Vec<char> vertices;
//             Vec<char> indices;
//         };

//         class BatchRenderer {
//             public:
//             /**
//              * @brief Create a batch renderer.
//              * @param layout The layout of the vertices. The shaders for the
//              *                materials rendered must be compatible with this layout.
//              * @return The batch renderer.
//              */
//             BatchRenderer(gl::VAOLayout layout);
//             /**
//              * @brief Destroy the batch renderer.
//              */
//             ~BatchRenderer();

//             /**
//              * @brief Batch a mesh.
//              * @param mesh The mesh to batch.
//              */
//             void batch(BatchMesh& mesh);
//             /**
//              * @brief Render all the batched vertices.
//              */
//             void flush();

//             private:
//             const Raster3D renderer;  // The renderer used to render the batches.
//             const UMap<MaterialPBR,
//                        Batch> batches;  // The batches.
//         };
//     }  // namespace core::gfx
// }  // namespace cobalt