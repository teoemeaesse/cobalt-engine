// Created by tomas on
// 08-12-2023

#include "engine/render/node.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        RenderNode::RenderNode(Renderer& renderer) : renderer(renderer) {}

        RenderNode::RenderNode(const RenderNode& other) : renderer(other.renderer), sources(other.sources), outputs(other.outputs) {}

        RenderNode::RenderNode(RenderNode&& other) noexcept : renderer(other.renderer), sources(Move(other.sources)), outputs(Move(other.outputs)) {}

        void RenderNode::renderMesh(Mesh& mesh) {
            if (outputs.size() == 0) {
                CB_CORE_WARN("Render node has no outputs");
            }
            for (uint i = 0; i < sources.size(); i++) {
                uint binding = renderer.bindTexture("source_" + sources[i].getName(), sources[i].getFBO().getColorBuffer().value());
            }
            renderer.bindMaterial(mesh.getMaterial());
            for (uint i = 0; i < outputs.size(); i++) {
                renderer.renderMesh(mesh, outputs[i], cameras.at(outputs[i].getName()).getCamera());
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::renderSkybox(Skybox& skybox) {
            if (outputs.size() == 0) {
                CB_CORE_WARN("Render node has no outputs");
            }
            renderer.bindTexture("skybox", skybox.getTexture());
            for (uint i = 0; i < outputs.size(); i++) {
                renderer.renderSkybox(skybox, outputs[i], cameras.at(outputs[i].getName()).getCamera());
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::addSource(RenderTarget&& source) { sources.push_back(Move(source)); }

        void RenderNode::addOutput(const CameraID& cameraID, RenderTarget&& output) {
            cameras.emplace(output.getName(), cameraID);
            outputs.push_back(Move(output));
        }

        Vec<RenderTarget>& RenderNode::getSources() { return sources; }

        Vec<RenderTarget>& RenderNode::getOutputs() { return outputs; }
    }  // namespace engine
}  // namespace cobalt