// Created by tomas on
// 08-12-2023

#include "engine/render/node.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        RenderNode::RenderNode(const RenderNode& other) : renderer(other.renderer), sources(other.sources), targets(other.targets) {}

        RenderNode::RenderNode(RenderNode&& other) noexcept : renderer(other.renderer), sources(Move(other.sources)), targets(Move(other.targets)) {}

        void RenderNode::renderMesh(Mesh& mesh, const CameraManager& cameraManager) {
            if (targets.size() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            for (uint i = 0; i < sources.size(); i++) {
                uint binding = renderer.bindTexture("source_" + sources[i].getName(), sources[i].getFBO().getColorBuffer().value());
            }
            renderer.bindMaterial(mesh.getMaterial());
            for (uint i = 0; i < targets.size(); i++) {
                renderer.renderMesh(mesh, targets[i], cameraManager);
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::renderSkybox(Skybox& skybox, const CameraManager& cameraManager) {
            if (targets.size() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            renderer.bindTexture("skybox", skybox.getTexture());
            for (uint i = 0; i < targets.size(); i++) {
                renderer.renderSkybox(skybox, targets[i], cameraManager);
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::addSource(RenderTarget&& source) { sources.push_back(Move(source)); }

        Vec<RenderTarget>& RenderNode::getSources() { return sources; }

        Vec<RenderTarget>& RenderNode::getTargets() { return targets; }
    }  // namespace engine
}  // namespace cobalt