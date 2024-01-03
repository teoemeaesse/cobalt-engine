//
// Created by tomas on 10-12-2023.
//

#pragma once

#include "core/gfx/render_graph.h"


namespace cobalt {
    namespace engine {
        class DefaultGraph : public core::RenderGraph {
            public:
            /** Creates a default render graph.
             * @param scene: The scene to render.
             * @param defaultFBO: The default FBO to render the final image to.
             * @return: A default render graph.
             */
            DefaultGraph(core::Scene& scene, core::DefaultFBO& defaultFBO);
            /** Destroys the default render graph.
             */
            ~DefaultGraph() = default;

            /** Initializes the render graph.
             */
            void init();

            /** Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             */
            void onResize(const uint width, const uint height) override;

            private:
            core::CameraController output;  // The camera used to render the final image.
            core::Renderer renderer;        // The renderer used to render the scene.
            core::DefaultFBO& defaultFBO;   // The default FBO to render the final image to.
            core::TargetFBO sceneFBO;       // The FBO to render the scene to.
            core::Scene& scene;             // The scene to render.
        };
    }
}