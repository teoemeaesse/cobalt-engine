//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/default_graph.h"
#include "engine/gfx/scene_node.h"
#include "engine/gfx/filter_node.h"
#include "engine/internal/shader_library.h"
#include "engine/internal/material_library.h"


namespace cobalt {
    namespace engine {
        DefaultGraph::DefaultGraph(core::Scene& scene, core::DefaultFBO& defaultFBO) : core::RenderGraph(),
            outputCamera(glm::vec3(0.0, 0.0, 10.0),
                         glm::vec2(90.0, 90.0),
                         -(float) defaultFBO.getWidth() / 2, (float) defaultFBO.getWidth() / 2,
                         -(float) defaultFBO.getHeight() / 2, (float) defaultFBO.getHeight() / 2,
                         1.0f, 100.0f),
            renderer(core::Renderer()),
            defaultFBO(defaultFBO),
            sceneFBO(core::TargetFBO(defaultFBO.getWidth(), defaultFBO.getHeight(), core::GLFramebufferAttachment::ColorDepth)),
            scene(scene) {
        }

        void DefaultGraph::init() {
            core::Material& filter = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makeFromShader("filterMaterial", "filter"));
            Scope<SceneNode> sceneNode = createScope<SceneNode>(SceneNode(scene, renderer, core::RenderTarget(sceneFBO, scene.getCamera(), "scene", 0)));
            Scope<FilterNode> filterNode = createScope<FilterNode>(FilterNode(renderer, core::RenderTarget(defaultFBO, outputCamera, "output", 1), filter));
            filterNode->addSource(core::RenderTarget(sceneFBO, scene.getCamera(), "scene", 0));

            addNode(std::move(sceneNode));
            addNode(std::move(filterNode));
        }

        void DefaultGraph::onResize(const uint width, const uint height) {
            outputCamera.resize(-(float) width / 2, (float) width / 2, -(float) height / 2, (float) height / 2);
            sceneFBO.resize(width, height);
            for (uint i = 0; i < nodes.size(); i++) {
                nodes[i]->onResize(width, height);
            }
        }
    }
}