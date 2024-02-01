// Created by tomas on
// 10-12-2023

#pragma once

#include "core/gfx/render_graph.h"

namespace cobalt {
    namespace engine {
        class DefaultGraph : public core::gfx::RenderGraph {
            public:
            /**
             * @brief: Creates a default render graph.
             * @param scene: The scene to render.
             * @param defaultFBO: The default FBO to render the final image to.
             * @return: A default render graph.
             */
            DefaultGraph(core::scene::Scene& scene, core::gl::FBO& defaultFBO);
            /**
             * @brief: Destroys the default render graph.
             */
            ~DefaultGraph() = default;

            /**
             * @brief: Initializes the render graph.
             * @return: void
             */
            void init();

            /**
             * @brief: Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             * @return: void
             */
            void onResize(const uint width, const uint height) override;

            private:
            core::gfx::CameraController output;  // The camera used to render the final image.
            core::gfx::Renderer renderer;        // The renderer used to render the scene.
            core::gl::FBO& defaultFBO;           // The default FBO to render the final image to.
            core::gl::FBO sceneFBO;              // The FBO to render the scene to.
            core::scene::Scene& scene;           // The scene to render.
        };
    }  // namespace engine
}  // namespace cobalt