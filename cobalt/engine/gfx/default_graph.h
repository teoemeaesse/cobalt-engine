// Created by tomas on
// 10-12-2023

#pragma once

#include "engine/render/graph.h"
#include "engine/scene/plugin.h"

namespace cobalt {
    namespace engine {
        class DefaultGraph : public RenderGraph {
            public:
            /**
             * @brief Creates a default render graph.
             * @param scene The scene to render.
             * @param cameraManager The camera manager to use.
             * @param defaultFBO The default FBO to render the final image to.
             * @return A default render graph.
             */
            DefaultGraph(Scene& scene, CameraManager& cameraManager, core::gl::FBO& defaultFBO);
            /**
             * @brief Destroys the default render graph.
             */
            ~DefaultGraph() = default;

            /**
             * @brief Initializes the render graph.
             */
            void init();

            /**
             * @brief Called upon window resize.
             * @param width The new width of the render graph.
             * @param height The new height of the render graph.
             */
            void onResize(const uint width, const uint height) override;

            private:
            const CameraManager& cameraManager;  // The camera manager to use.
            const CameraID outputCameraID;       // The ID for the camera used to render the final image.
            Renderer renderer;                   // The renderer used to render the scene.
            core::gl::FBO& defaultFBO;           // The default FBO to render the final image to.
            core::gl::FBO sceneFBO;              // The FBO to render the scene to.
            Scene& scene;                        // The scene to render.
        };
    }  // namespace engine
}  // namespace cobalt