//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/default_graph.h"
#include "engine/gfx/scene_node.h"
#include "engine/gfx/filter_node.h"
#include "engine/internal/shader_library.h"
#include "engine/internal/texture_library.h"


namespace cobalt {
    namespace engine {
        DefaultGraph::DefaultGraph(core::Scene& scene, core::DefaultFBO& defaultFBO) : core::RenderGraph(),
            outputCamera(glm::vec3(0.0, 0.0, 10.0),
                         glm::vec2(90.0, 90.0),
                         0.0f,
                         -(float) defaultFBO.getWidth() / 2, (float) defaultFBO.getWidth() / 2,
                         -(float) defaultFBO.getHeight() / 2, (float) defaultFBO.getHeight() / 2,
                         1.0f, 100.0f),
            renderer(core::Renderer()),
            defaultFBO(defaultFBO),
            sceneFBO(core::TargetFBO(defaultFBO.getWidth(), defaultFBO.getHeight(), core::GLFramebufferAttachment::ColorDepth)),
            scene(scene) {
        }

        void DefaultGraph::init() {
            core::Material* filter = new core::Material(
                CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("filter_shader")),
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("metal-albedo")),
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("metal-albedo")),
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("metal-albedo"))
            );
            Scope<SceneNode> sceneNode = std::make_unique<SceneNode>(SceneNode(scene, renderer, core::RenderTarget(sceneFBO, scene.getCamera(), "scene")));
            Scope<FilterNode> filterNode = std::make_unique<FilterNode>(FilterNode(renderer, core::RenderTarget(defaultFBO, outputCamera, "output"), filter));
            filterNode->addSource(core::RenderTarget(sceneFBO, scene.getCamera(), "scene"));

            addNode(std::move(sceneNode));
            addNode(std::move(filterNode));
        }

        void DefaultGraph::onResize(const float width, const float height) {
            outputCamera.resize(-width / 2, width / 2, -height / 2, height / 2);
            sceneFBO.resize((uint) width, (uint) height);
            for (uint i = 0; i < nodes.getSize(); i++) {
                nodes[i]->onResize(width, height);
            }
        }
    }
}