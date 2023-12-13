//
// Created by tomas on 10-12-2023.
//

#pragma once

#include "core/gfx/render_node.h"
#include "core/scene/scene.h"


namespace cobalt {
    namespace engine {
        /* Scene node. Renders a full scene.
         */
        class SceneNode : public core::RenderNode {
            public:
            /* Create a scene node with a scene.
             * @param scene: The scene to render.
             * @param targets: The targets to render to.
             * @return: The scene node.
             */
            template <typename... Targets>
            SceneNode(core::Scene& scene, core::Renderer& renderer, Targets&&... targets) : RenderNode(renderer, targets...),
                scene(scene)
            {}
            /* Destroy the scene node.
             */
            ~SceneNode() = default;

            /* Render the scene.
             */
            void render() override;

            private:
            core::Scene& scene;   // The scene to render.
        };
    }
}