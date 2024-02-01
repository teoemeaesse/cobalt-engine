// Created by tomas on
// 10-12-2023

#pragma once

#include "core/gfx/render_node.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Applies a color filter to the final image.
         */
        class FilterNode : public core::gfx::RenderNode {
            public:
            /**
             * @brief: Create a filter node.
             * @param renderer: The renderer to use.
             * @param defaultTarget: The default target to render to. This is the target
             *                       that contains the final image.
             * @param filter: The material to use for the filter quad.
             * @return: The filter node.
             */
            FilterNode(core::gfx::Renderer& renderer, core::gfx::RenderTarget&& defaultTarget, core::gfx::Material& filter);
            /**
             * @brief: Destroy the filter node.
             */
            ~FilterNode() = default;

            /**
             * @brief: Render the filter to the final image.
             * @return: void
             */
            void render() override;
            /**
             * @brief: Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             * @return: void
             */
            void onResize(const float width, const float height) override;

            private:
            core::gfx::Material& filter;  // The material to use for the filter quad.
            uint width, height;           // The width and height of the filter quad.
        };
    }  // namespace engine
}  // namespace cobalt