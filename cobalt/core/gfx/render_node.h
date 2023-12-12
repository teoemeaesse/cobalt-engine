//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/renderer.h"
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
            /* Create a render node with a renderer.
             * @param renderer: The renderer to use for rendering.
             * @param targets: The targets to render to.
             * @return: The render node.
             */
            template<typename... Targets>
            RenderNode(Renderer& renderer, Targets&&... targets)
                : renderer(renderer),
                  sources(1),
                  targets(sizeof...(targets))
            {
                ((this->targets.push(std::move(targets))), ...);
            }
            /* Destroy the render node.
             */
            ~RenderNode() = default;

            /* Render to the targets, binding the sources
             * to the adequate texture units.
             * Each render node should override this method
             * and call the protected render method.
             */
            virtual void render();

            /* Add a source to the render node. It will be bound
             * to the next available texture unit.
             * @param source: The source to add.
             */
            void addSource(RenderTarget&& source);

            private:
            Vector<RenderTarget> sources;   // The list of sources.
            Vector<RenderTarget> targets;   // The list of targets.
            
            protected:
            Renderer& renderer;             // The renderer to use.
            
            /* Render to the targets, binding the sources
             * to the adequate texture units.
             * Each render node should decide how to call
             * this method.
             * @param mesh: The mesh to render.
             */
            void render(Mesh& mesh);
        };
    }
}