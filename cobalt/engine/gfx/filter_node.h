// Created by tomas on
// 10-12-2023

#pragma once

#include "engine/render/node.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Applies a color filter to the final image.
         */
        class FilterNode : public RenderNode {
            public:
            /**
             * @brief Create a filter node.
             * @param filter The material to use for the filter quad.
             * @param renderer The renderer to use.
             * @param cameraID The camera to render with.
             * @param defaultTarget The default target to render to. This is the target that contains the final image.
             * @return The filter node.
             */
            FilterNode(Material& filter, Raster3D& renderer, const CameraID& cameraID, RenderTarget&& defaultTarget);
            /**
             * @brief Destroy the filter node.
             */
            ~FilterNode() = default;

            /**
             * @brief Render the filter to the final image.
             * @param world The world to render.
             */
            void render(const core::ecs::World& world) override;
            /**
             * @brief Called upon window resize.
             * @param width The new width of the render graph.
             * @param height The new height of the render graph.
             */
            void onResize(const float width, const float height) override;

            private:
            Material& filter;    // The material to use for the filter quad.
            uint width, height;  // The width and height of the filter quad.
        };
    }  // namespace engine
}  // namespace cobalt