//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/scene_node.h"
#include "core/gfx/render_context.h"


namespace cobalt {
    namespace engine {
        void SceneNode::render() {
            auto& meshes = scene.getMeshes();
            for (uint i = 0; i < meshes.getSize(); i++) {
                core::RenderNode::renderMesh(meshes[i]);
            }
            if (scene.getSkybox().has_value()) {
                core::RenderNode::renderSkybox(scene.getSkybox().value());
            }
        }

        void SceneNode::onResize(const float width, const float height) {
            // Empty
        }
    }
}