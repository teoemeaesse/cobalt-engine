//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/mesh.h"
#include "core/gfx/render_target.h"


namespace cobalt {
    namespace core {
        class MeshRenderer {
            public:
            /* Create a mesh renderer.
             * @param target: The render target.
             * @return: The renderer.
             */
            MeshRenderer(RenderTarget& target);
            /* Destroy the renderer.
             */
            ~MeshRenderer() = default;

            /* Render call.
             * @param mesh: The mesh to render.
             */
            void render(Mesh& mesh) const;

            private:
            RenderTarget& target;   // Render target.
        };
    }
}