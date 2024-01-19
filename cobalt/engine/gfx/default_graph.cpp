// Created by tomas on
// 10-12-2023

#include "engine/gfx/default_graph.h"

#include "engine/gfx/filter_node.h"
#include "engine/gfx/scene_node.h"
#include "engine/internal/material_library.h"
#include "engine/internal/shader_library.h"

namespace cobalt {
    namespace engine {
        DefaultGraph::DefaultGraph(core::scene::Scene& scene, core::gl::FBO& defaultFBO)
            : core::gfx::RenderGraph(),
              output(core::gfx::CameraController::create<core::gfx::OrthographicCamera>(
                  core::gfx::CameraProperties()
                      .setPosition(glm::vec3(0.0, 0.0, 10.0))
                      .setDirection(glm::vec2(90.0, 90.0))
                      .setOrthoPlanes(-(float)defaultFBO.getWidth() / 2, (float)defaultFBO.getWidth() / 2, -(float)defaultFBO.getHeight() / 2,
                                      (float)defaultFBO.getHeight() / 2)
                      .setClippingPlanes(1.0f, 100.0f))),
              renderer(core::gfx::Renderer()),
              defaultFBO(defaultFBO),
              sceneFBO(defaultFBO.getWidth(), defaultFBO.getHeight(),
                       {{core::gl::TextureEncodings::RGBA::Bits8}, {core::gl::TextureEncodings::Depth::Bits24}}),
              scene(scene) {}

        void DefaultGraph::init() {
            core::gfx::Material& filter = CB_MATERIAL_LIBRARY.getMaterial(CB_MATERIAL_LIBRARY.makeFromShader("filterMaterial", "filter"));
            Scope<SceneNode> sceneNode = createScope<SceneNode>(
                SceneNode(scene, renderer, core::gfx::RenderTarget(sceneFBO, scene.getCameraController().getCamera(), "scene", 0)));
            Scope<FilterNode> filterNode =
                createScope<FilterNode>(FilterNode(renderer, core::gfx::RenderTarget(defaultFBO, output.getCamera(), "output", 1), filter));
            filterNode->addSource(core::gfx::RenderTarget(sceneFBO, scene.getCameraController().getCamera(), "scene", 0));

            addNode(std::move(sceneNode));
            addNode(std::move(filterNode));
        }

        void DefaultGraph::onResize(const uint width, const uint height) {
            output.resize(-(float)width / 2, (float)width / 2, -(float)height / 2, (float)height / 2);
            sceneFBO.resize(width, height);
            for (uint i = 0; i < nodes.size(); i++) {
                nodes[i]->onResize(width, height);
            }
        }
    }  // namespace engine
}  // namespace cobalt