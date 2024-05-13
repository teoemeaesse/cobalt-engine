// Created by tomas on
// 10-12-2023

#pragma once

#include "engine/render/node.h"
#include "engine/scene/scene.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Scene node. Renders a full scene.
         */
        class SceneNode : public RenderNode {
            public:
            /**
             * @brief Create a scene node with a scene.
             * @param scene The scene to render.
             * @param renderer The renderer to use for rendering.
             * @return The scene node.
             */
            SceneNode(Scene& scene, Raster3D& renderer);
            /**
             * @brief Destroy the scene node.
             */
            ~SceneNode() = default;

            /**
             * @brief Render the scene.
             */
            void render() override;
            /**
             * @brief Called upon window resize.
             * @param width The new width of the render graph.
             * @param height The new height of the render graph.
             */
            void onResize(const float width, const float height) override;

            private:
            Scene& scene;  // The scene to render.
        };
    }  // namespace engine
}  // namespace cobalt