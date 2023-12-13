//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/default_graph.h"
#include "engine/gfx/scene_node.h"
#include "engine/gfx/filter_node.h"


namespace cobalt {
    namespace engine {
        DefaultGraph::DefaultGraph(core::Scene& scene, const core::FBO& defaultFBO) : core::RenderGraph(),
            outputCamera(glm::vec3(0.0, 0.0, 10.0),
                         glm::vec2(-1.57079633f, 0.0f),
                         0.1f,
                         -(float) defaultFBO.getWidth() / 2, (float) defaultFBO.getWidth() / 2,
                         -(float) defaultFBO.getHeight() / 2, (float) defaultFBO.getHeight() / 2,
                         1.0f, 1000.0f),
            renderer(core::Renderer()) {
            core::RenderTarget renderTarget(defaultFBO, outputCamera, "output");
            addNode(std::move(std::make_unique<SceneNode>(std::move(SceneNode(scene, renderer, std::move(renderTarget))))));
        }
    }
}