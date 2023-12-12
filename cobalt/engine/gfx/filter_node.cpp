//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/filter_node.h"


namespace cobalt {
    namespace engine {
        FilterNode::FilterNode(core::Renderer& renderer, core::RenderTarget* defaultTarget, core::Material* filter) : RenderNode(renderer, defaultTarget),
            filter(filter)
        {}

        void FilterNode::render() { // TODO: Fix these width and height values.
            core::Mesh filterMesh = core::Mesh::createRectangle(100, 100, filter);
            RenderNode::render(filterMesh);
        }
    }
}