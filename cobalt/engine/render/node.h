// Created by tomas on
// 08-12-2023

#pragma once

#include "engine/renderer3d/renderer.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: A render node is a node in a graph that connects
         * source render targets to output render targets
         * using a single renderer.
         */
        class RenderNode {
            public:
            /**
             * @brief: Create a render node with a renderer.
             * @param renderer: The renderer to use for rendering.
             * @param targets: The targets to render to.
             * @return: The render node.
             */
            template <typename... Targets>
            RenderNode(Renderer& renderer, Targets&&... targets) : renderer(renderer) {
                ((this->targets.push_back(Move(targets))), ...);
            }
            /**
             * @brief: Destroy the render node.
             */
            virtual ~RenderNode() = default;
            /**
             * @brief: Copy constructor.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode(const RenderNode&);
            /**
             * @brief: Move constructor.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode(RenderNode&&) noexcept;
            /**
             * @brief: Copy assignment.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode& operator=(const RenderNode&) = delete;
            /**
             * @brief: Move assignment.
             * @param other: The other render node.
             * @return: The render node.
             */
            RenderNode& operator=(RenderNode&&) = delete;

            /**
             * @brief: Render to the targets, binding the sources to the adequate texture units. Each render node should override this method and call
             * the protected render method.
             * @return: void
             */
            virtual void render() = 0;
            /**
             * @brief: Called when the window is resized.
             * @param width: The new width.
             * @param height: The new height.
             * @return: void
             */
            virtual void onResize(const float width, const float height) = 0;

            /**
             * @brief: Add a source to the render node. It will be bound
             * to the next available texture unit.
             * @param source: The source to add.
             * @return: void
             */
            void addSource(RenderTarget&& source);

            /**
             * @brief: Get the sources.
             * @return: The sources.
             */
            Vec<RenderTarget>& getSources();
            /**
             * @brief: Get the targets.
             * @return: The targets.
             */
            Vec<RenderTarget>& getTargets();

            protected:
            Vec<RenderTarget> sources;  // The list of sources.
            Vec<RenderTarget> targets;  // The list of targets.
            Renderer& renderer;         // The renderer to use.

            /**
             * @brief: Render to the targets, binding the sources to the adequate texture units. Each render node should decide how to call this
             * method.
             * @param mesh: The mesh to render.
             * @return: void
             */
            void renderMesh(Mesh& mesh);

            /**
             * @brief: Render a skybox to the targets. Each render node should decide how to call this method.
             * @param skybox: The skybox to render.
             * @return: void
             */
            void renderSkybox(Skybox& skybox);
        };
    }  // namespace engine
}  // namespace cobalt