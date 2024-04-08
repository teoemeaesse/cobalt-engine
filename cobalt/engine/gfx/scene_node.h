// Created by tomas on
// 10-12-2023

#pragma once

#include "engine/render/node.h"
#include "engine/scene/scene.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Scene node. Renders a full scene.
         */
        class SceneNode : public RenderNode {
            public:
            /**
             * @brief: Create a scene node with a scene.
             * @param scene: The scene to render.
             * @param targets: The targets to render to.
             * @return: The scene node.
             */
            template <typename... Targets>
            SceneNode(Scene& scene, Renderer& renderer, Targets&&... targets) : RenderNode(renderer, targets...), scene(scene) {}
            /**
             * @brief: Destroy the scene node.
             */
            ~SceneNode() = default;

            /**
             * @brief: Render the scene.
             * @param cameraManager: The camera manager.
             * @return: void
             */
            void render(const CameraManager& cameraManager) override;
            /**
             * @brief: Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             * @return: void
             */
            void onResize(const float width, const float height) override;

            private:
            Scene& scene;  // The scene to render.
        };
    }  // namespace engine
}  // namespace cobalt