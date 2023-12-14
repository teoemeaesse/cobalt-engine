//
// Created by tomas on 10-12-2023.
//

#include "engine/gfx/filter_node.h"


namespace cobalt {
    namespace engine {
        FilterNode::FilterNode(core::Renderer& renderer, core::RenderTarget&& defaultTarget, core::Material* filter) : RenderNode(renderer, std::move(defaultTarget)),
            filter(filter),
            width(defaultTarget.getFBO().getWidth()),
            height(defaultTarget.getFBO().getHeight())
        {}

        void FilterNode::render() {
            core::Mesh filterMesh = core::Mesh::createRectangle(
                width,
                height,
                filter
            );
            RenderNode::render(filterMesh);
        }

        void FilterNode::onResize(const float width, const float height) {
            this->width = width;
            this->height = height;
        }
    }
}