//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_node.h"
#include "core/gfx/render_context.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        RenderNode::RenderNode(const RenderNode& other) : 
            renderer(other.renderer),
            sources(other.sources),
            targets(other.targets) {
        }

        RenderNode::RenderNode(RenderNode&& other) noexcept : 
            renderer(other.renderer),
            sources(std::move(other.sources)),
            targets(std::move(other.targets)) {
        }

        void RenderNode::renderMesh(Mesh& mesh) {
            if (targets.size() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            for (uint i = 0; i < sources.size(); i++) {
                uint binding = renderer.bindTexture("source_" + sources[i].getName(), sources[i].getColorBuffer());
            }
            renderer.bindTexture("albedo", mesh.getMaterial().getAlbedoMap());
            renderer.bindTexture("normal", mesh.getMaterial().getNormalMap());
            renderer.bindTexture("mrao", mesh.getMaterial().getMRAOMap());
            for (uint i = 0; i < targets.size(); i++) {
                renderer.renderMesh(mesh, targets[i]);
            }
            renderer.clearTextureUnits();
        }
        
        void RenderNode::renderSkybox(Skybox& skybox) {
            if (targets.size() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            renderer.bindTexture("skybox", skybox.getTexture());
            for (uint i = 0; i < targets.size(); i++) {
                renderer.renderSkybox(skybox, targets[i]);
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::addSource(RenderTarget&& source) {
            sources.push_back(std::move(source));
        }

        Vec<RenderTarget>& RenderNode::getSources() {
            return sources;
        }

        Vec<RenderTarget>& RenderNode::getTargets() {
            return targets;
        }
    }
}