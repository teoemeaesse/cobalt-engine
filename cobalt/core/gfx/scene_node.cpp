//
// Created by tomas on 10-12-2023.
//

#include "core/gfx/scene_node.h"


namespace cobalt {
    namespace core {
        void SceneNode::render() {
            auto& meshes = scene.getMeshes();
            for (uint i = 0; i < meshes.getSize(); i++) {
                RenderNode::render(*scene.getMeshes()[i]);
            }
        }
    }
}