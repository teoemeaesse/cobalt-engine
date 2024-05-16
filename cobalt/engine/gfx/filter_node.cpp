// Created by tomas on
// 10-12-2023

#include "engine/gfx/filter_node.h"

#include "engine/mesh3d/plugin.h"

namespace cobalt {
    using namespace core;
    namespace engine {
        FilterNode::FilterNode(Material& filter, Raster3D& renderer, const CameraID& cameraID, RenderTarget&& defaultTarget)
            : RenderNode(renderer), filter(filter), width(defaultTarget.getFBO().getWidth()), height(defaultTarget.getFBO().getHeight()) {
            addOutput(cameraID, Move(defaultTarget));
        }

        void FilterNode::render() {
            Mesh filterMesh = Mesh3DPlugin::createRectangle(width, height, filter);
            RenderNode::renderMesh(filterMesh);
        }

        void FilterNode::onResize(const float width, const float height) {
            this->width = width;
            this->height = height;
        }
    }  // namespace engine
}  // namespace cobalt