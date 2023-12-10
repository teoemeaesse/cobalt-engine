//
// Created by tomas on 10-12-2023.
//

#include "core/gfx/filter_node.h"


namespace cobalt {
    namespace core {
        FilterNode::FilterNode(Renderer& renderer, RenderTarget& defaultTarget, Material& filter) : RenderNode(renderer, defaultTarget),
            filter(filter)
        {}

        void FilterNode::render() { // TODO: Fix these width and height values.
            Mesh filterMesh = Mesh::createRectangle(100, 100, filter);
            RenderNode::render(filterMesh);
        }
    }
}