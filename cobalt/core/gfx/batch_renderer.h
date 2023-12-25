//
// Created by tomas on 23-12-2023.
//

#pragma once

#include "core/pch.h"
#include "core/gfx/renderer.h"
#include "core/gfx/batch_mesh.h"


namespace cobalt {
    namespace core {
        class Batch {
            public:
            Batch();
            ~Batch();

            /** Add a mesh to the batch.
             * @param mesh: The mesh to add.
             */
            void add(BatchMesh& mesh);

            private:
            Vec<char> vertices;
            Vec<char> indices;
        };

        class BatchRenderer {
            public:
            /** Create a batch renderer.
             * @param layout: The layout of the vertices. The shaders for the
             *                materials rendered must be compatible with this layout.
             * @return: The batch renderer.
             */
            BatchRenderer(VAOLayout layout);
            /** Destroy the batch renderer.
             */
            ~BatchRenderer();
            
            /** Batch a mesh.
             * @param mesh: The mesh to batch.
             */
            void batch(BatchMesh& mesh);
            /** Render all the batched vertices.
             */
            void flush();
            
            private:
            const Renderer renderer;                // The renderer used to render the batches.
            const UMap<Material, Batch> batches;    // The batches.
        };
    }
}