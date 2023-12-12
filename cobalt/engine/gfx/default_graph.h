//
// Created by tomas on 10-12-2023.
//

#pragma once

#include "core/gfx/render_graph.h"


namespace cobalt {
    namespace engine {
        class DefaultGraph : public core::RenderGraph {
            public:
            /* Creates a default render graph.
             * @param scene: The scene to render.
             * @param defaultFBO: The default FBO to render the final image to.
             * @return: A default render graph.
             */
            DefaultGraph(core::Scene& scene, const core::FBO& defaultFBO);
            /* Destroys the default render graph.
             */
            ~DefaultGraph() = default;

            private:
            core::OrthographicCamera outputCamera;  // The camera used to render the final image.
        };
    }
}