//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/mesh.h"


namespace cobalt {
    namespace core {
        class MeshRenderer {
            public:
            /* Create a mesh renderer.
             * @return: The renderer.
             */
            MeshRenderer() = default;
            /* Destroy the renderer.
             */
            ~MeshRenderer() = default;

            /* Render call. 
             */
            void render(Mesh& mesh) const;
        };
    }
}