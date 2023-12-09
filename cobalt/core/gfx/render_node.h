//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/mesh_renderer.h"
#include "core/gfx/render_target.h"
#include "core/containers/vector.h"


namespace cobalt {
    namespace core {
        /* A render node is a node in a graph that connects
         * source render targets to output render targets
         * using a single renderer.
         */
        class RenderNode {
            public:
            /* Create a render stage with a renderer.
             * @param renderer: The renderer to use for rendering.
             * @param targets: The targets to render to.
             * @return: The render stage.
             */
            template<typename... Targets>
            RenderNode(MeshRenderer* renderer, Targets... targets)
                : renderer(renderer),
                  sources(1),
                  targets(sizeof...(targets))
            {
                uint i = 0;
                ((this->targets[i++] = targets), ...);
            }
            /* Destroy the render stage.
             */
            ~RenderNode() = default;

            /* Render to the targets, binding the sources
             * to the adequate texture units.
             * @param mesh: The mesh to render.
             */
            void render(Mesh& mesh);

            void addSource(RenderTarget& source) {
                sources.push(source);
            }


            private:
            MeshRenderer* renderer;         // The renderer to use.
            Vector<RenderTarget> sources;  // The list of sources.
            Vector<RenderTarget> targets;  // The list of targets.
        };
    }
}