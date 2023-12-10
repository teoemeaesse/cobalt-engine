//
// Created by tomas on 10-12-2023.
//

#pragma once

#include "core/gfx/render_node.h"


namespace cobalt {
    namespace core {
        /* Applies a color filter to the final image.
         */
        class FilterNode : public RenderNode {
            public:
            /* Create a filter node.
             * @param renderer: The renderer to use.
             * @param defaultTarget: The default target to render to. This is the target
             *                       that contains the final image.
             * @param filter: The material to use for the filter quad.
             * @return: The filter node.
             */
            FilterNode(Renderer& renderer, RenderTarget& defaultTarget, Material& filter);
            /* Destroy the filter node.
             */
            ~FilterNode() = default;

            /* Render the filter to the final image.
             */
            void render() override;

            private:
            Material& filter;   // The material to use for the filter quad.
        };
    }
}