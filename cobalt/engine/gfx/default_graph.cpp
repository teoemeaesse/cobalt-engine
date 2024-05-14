// Created by tomas on
// 10-12-2023

#include "engine/gfx/default_graph.h"

#include "engine/gfx/filter_node.h"
#include "engine/gfx/scene_node.h"
#include "engine/internal/shader_library.h"
#include "engine/material/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        DefaultGraph::DefaultGraph(Scene& scene, CameraManager& cameraManager, core::gl::FBO& defaultFBO)
            : RenderGraph(),
              outputCameraID(cameraManager.addCamera<OrthographicCamera>(
                  "output_camera", CameraProperties()
                                       .setPosition(glm::vec3(0.0, 0.0, 10.0))
                                       .setDirection(glm::vec2(90.0, 90.0))
                                       .setOrthoPlanes(-(float)defaultFBO.getWidth() / 2, (float)defaultFBO.getWidth() / 2,
                                                       -(float)defaultFBO.getHeight() / 2, (float)defaultFBO.getHeight() / 2)
                                       .setClippingPlanes(1.0f, 100.0f))),
              renderer(),
              defaultFBO(defaultFBO),
              sceneFBO(defaultFBO.getWidth(), defaultFBO.getHeight(),
                       {{core::gl::TextureEncodings::RGBA::Bits8}, {core::gl::TextureEncodings::Depth::Bits24}}),
              scene(scene) {}

        void DefaultGraph::init(core::ecs::World& world) {
            Material& filter = getMaterialLibrary(world).getMaterial(getMaterialLibrary(world).makeFromShader("filterMaterial", "filter"));
            Scope<SceneNode> sceneNode = CreateScope<SceneNode>(scene, renderer);
            Scope<FilterNode> filterNode = CreateScope<FilterNode>(filter, renderer, outputCameraID, RenderTarget(defaultFBO, "output"));

            sceneNode->addOutput(scene.getCameraID(), RenderTarget(sceneFBO, "scene"));
            filterNode->addSource(RenderTarget(sceneFBO, "scene"));

            addNode(Move(sceneNode));
            addNode(Move(filterNode));
        }

        void DefaultGraph::onResize(const uint width, const uint height) {
            // output.resize(-(float)width / 2, (float)width / 2, -(float)height / 2, (float)height / 2);
            sceneFBO.resize(width, height);
            for (uint i = 0; i < nodes.size(); i++) {
                // nodes[i]->onResize(width, height);
            }
        }
    }  // namespace engine
}  // namespace cobalt