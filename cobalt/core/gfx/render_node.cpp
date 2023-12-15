//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_node.h"
#include "core/utils/log.h"
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

        void RenderNode::render(Mesh& mesh) {
            if (targets.getSize() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }
            for (uint i = 0; i < sources.getSize(); i++) {
                uint binding = renderer.bindTexture("source_" + sources[i].getName(), sources[i].getTexture());
            }
            
            CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-albedo")).bindToUnit(6);
            CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-normal")).bindToUnit(7);
            CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-mrao")).bindToUnit(8);
            for (uint i = 0; i < targets.getSize(); i++) {
                renderer.render(mesh, targets[i]);
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