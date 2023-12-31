//
// Created by tomas on 10-12-2023.
//

#pragma once

#include "core/gfx/render_node.h"


namespace cobalt {
    namespace engine {
        /** Applies a color filter to the final image.
         */
        class FilterNode : public core::RenderNode {
            public:
            /** Create a filter node.
             * @param renderer: The renderer to use.
             * @param defaultTarget: The default target to render to. This is the target
             *                       that contains the final image.
             * @param filter: The material to use for the filter quad.
             * @return: The filter node.
             */
            FilterNode(core::Renderer& renderer, core::RenderTarget&& defaultTarget, core::Material& filter);
            /** Destroy the filter node.
             */
            ~FilterNode() = default;

            /** Render the filter to the final image.
             */
            void render() override;
            /** Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             */
            void onResize(const float width, const float height) override;

            private:
            core::Material& filter; // The material to use for the filter quad.
            uint width, height;     // The width and height of the filter quad.
        };
    }
}