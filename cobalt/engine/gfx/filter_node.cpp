// Created by tomas on
// 10-12-2023

#include "engine/gfx/filter_node.h"

namespace cobalt {
    using namespace core;
    namespace engine {
        FilterNode::FilterNode(Renderer& renderer, RenderTarget&& defaultTarget, gfx::Material& filter)
            : RenderNode(renderer, Move(defaultTarget)),
              filter(filter),
              width(defaultTarget.getFBO().getWidth()),
              height(defaultTarget.getFBO().getHeight()) {}

        void FilterNode::render(const CameraManager& cameraManager) {
            Mesh filterMesh = MeshFactory::createRectangle(width, height, filter);
            RenderNode::renderMesh(filterMesh, cameraManager);
        }

        void FilterNode::onResize(const float width, const float height) {
            this->width = width;
            this->height = height;
        }
    }  // namespace engine
}  // namespace cobalt