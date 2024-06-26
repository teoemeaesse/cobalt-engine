// Created by tomas on
// 10-12-2023

#include "engine/gfx/scene_node.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        SceneNode::SceneNode(Scene& scene, Renderer& renderer) : RenderNode(renderer), scene(scene) {}

        void SceneNode::render() {
            if (scene.getSkybox().has_value()) {
                RenderNode::renderSkybox(scene.getSkybox().value());
            }
            auto& meshes = scene.getMeshes();
            for (uint i = 0; i < meshes.size(); i++) {
                RenderNode::renderMesh(meshes[i]);
            }
        }

        void SceneNode::onResize(const float width, const float height) {
            // Empty
        }
    }  // namespace engine
}  // namespace cobalt