// Created by tomas on
// 10-12-2023

#include "engine/gfx/filter_node.h"

namespace cobalt {
    namespace engine {
        FilterNode::FilterNode(core::gfx::Renderer& renderer, core::gfx::RenderTarget&& defaultTarget, core::gfx::Material& filter)
            : RenderNode(renderer, std::move(defaultTarget)),
              filter(filter),
              width(defaultTarget.getFBO().getWidth()),
              height(defaultTarget.getFBO().getHeight()) {}

        void FilterNode::render() {
            core::gfx::Mesh filterMesh = core::gfx::Mesh::createRectangle(width, height, filter);
            RenderNode::renderMesh(filterMesh);
        }

        void FilterNode::onResize(const float width, const float height) {
            this->width = width;
            this->height = height;
        }
    }  // namespace engine
}  // namespace cobalt