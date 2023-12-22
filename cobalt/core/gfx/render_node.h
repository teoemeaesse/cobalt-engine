//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/renderer.h"
#include "core/gfx/render_target.h"
#include "core/pch.h"


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
            virtual ~RenderNode() = default;
            /* Copy constructor.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode(const RenderNode&);
            /* Move constructor.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode(RenderNode&&) noexcept;
            /* Copy assignment.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode& operator=(const RenderNode&) = delete;
            /* Move assignment.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode& operator=(RenderNode&&) = delete;

            /* Render to the targets, binding the sources
             * to the adequate texture units.
             * Each render node should override this method
             * and call the protected render method.
             */
            virtual void render() = 0;
            /* Called when the window is resized.
             * @param width: The new width.
             * @param height: The new height.
             */
            virtual void onResize(const float width, const float height) = 0;

            /* Add a source to the render node. It will be bound
             * to the next available texture unit.
             * @param source: The source to add.
             */
            void addSource(RenderTarget&& source);


            /* Get the sources.
             * @return: The sources.
             */
            Vector<RenderTarget>& getSources();
            /* Get the targets.
             * @return: The targets.
             */
            Vector<RenderTarget>& getTargets();

            protected:
            Vector<RenderTarget> sources;   // The list of sources.
            Vector<RenderTarget> targets;   // The list of targets.
            Renderer& renderer;             // The renderer to use.
            
            /* Render to the targets, binding the sources
             * to the adequate texture units.
             * Each render node should decide how to call
             * this method.
             * @param mesh: The mesh to render.
             */
            void renderMesh(Mesh& mesh);

            /* Render a skybox to the targets.
             * Each render node should decide how to call
             * this method.
             * @param skybox: The skybox to render.
             */
            void renderSkybox(Skybox& skybox);
        };
    }
}