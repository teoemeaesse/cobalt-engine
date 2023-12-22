//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_node.h"
#include "core/pch.h"
#include "engine/internal/texture_library.h"


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
            if (targets.getSize() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            for (uint i = 0; i < sources.getSize(); i++) {
                uint binding = renderer.bindTexture("source_" + sources[i].getName(), sources[i].getColorBuffer());
            }
            const auto& albedo = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-albedo"));
            const auto& normal = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-normal"));
            const auto& mrao = CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-mrao"));
            renderer.bindTexture("albedo", albedo);
            renderer.bindTexture("normal", normal);
            renderer.bindTexture("mrao", mrao);
            for (uint i = 0; i < targets.getSize(); i++) {
                renderer.renderMesh(mesh, targets[i]);
            }
            renderer.clearTextureUnits();
        }
        
        void RenderNode::renderSkybox(Skybox& skybox) {
            if (targets.getSize() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            renderer.bindTexture("skybox", skybox.getTexture());
            for (uint i = 0; i < targets.getSize(); i++) {
                renderer.renderSkybox(skybox, targets[i]);
            }
            renderer.clearTextureUnits();
        }

        void RenderNode::addSource(RenderTarget&& source) {
            sources.push(std::move(source));
        }

        Vector<RenderTarget>& RenderNode::getSources() {
            return sources;
        }

        Vector<RenderTarget>& RenderNode::getTargets() {
            return targets;
        }
    }
}