//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/filter_node.h"


namespace cobalt {
    namespace engine {
        FilterNode::FilterNode(core::Renderer& renderer, core::RenderTarget&& defaultTarget, core::Material* filter) : RenderNode(renderer, std::move(defaultTarget)),
            filter(filter)
        {}

        void FilterNode::render() {
            core::Mesh filterMesh = core::Mesh::createRectangle(
                1000,
                1000,
                filter
            );
            RenderNode::render(filterMesh);
        }
    }
}