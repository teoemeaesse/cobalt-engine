// Created by tomas on
// 10-12-2023

#pragma once

#include "engine/camera/controller.h"
#include "engine/render/graph.h"

namespace cobalt {
    namespace engine {
        class DefaultGraph : public RenderGraph {
            public:
            /**
             * @brief Creates a default render graph.
             * @param scene The scene to render.
             * @param manager The camera manager to use.
             * @param defaultFBO The default FBO to render the final image to.
             * @return A default render graph.
             */
            DefaultGraph(Scene& scene, CameraManager& manager, core::gl::FBO& defaultFBO);
            /**
             * @brief Destroys the default render graph.
             */
            ~DefaultGraph() = default;

            /**
             * @brief Initializes the render graph.
             * @param manager The camera manager to use.
             */
            void init(CameraManager& manager);

            /**
             * @brief Called upon window resize.
             * @param width The new width of the render graph.
             * @param height The new height of the render graph.
             */
            void onResize(const uint width, const uint height) override;

            private:
            const CameraID output;      // The ID for the camera used to render the final image.
            Renderer renderer;          // The renderer used to render the scene.
            core::gl::FBO& defaultFBO;  // The default FBO to render the final image to.
            core::gl::FBO sceneFBO;     // The FBO to render the scene to.
            Scene& scene;               // The scene to render.
        };
    }  // namespace engine
}  // namespace cobalt