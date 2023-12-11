//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/default_graph.h"
#include "engine/gfx/scene_node.h"
#include "engine/gfx/filter_node.h"


namespace cobalt {
    namespace engine {
        DefaultGraph::DefaultGraph(core::Scene& scene, core::FBO& defaultFBO) : core::RenderGraph(),
            outputCamera(glm::vec3(0.0, 0.0, 1.0),
                         glm::vec2(0.0, 0.0),
                         0.0f,
                         0.0f, defaultFBO.getWidth(),
                         0.0f, defaultFBO.getHeight(),
                         0.0f, 1000.0f) {
            core::RenderTarget renderTarget(defaultFBO, outputCamera, "output");
        }
    }
}