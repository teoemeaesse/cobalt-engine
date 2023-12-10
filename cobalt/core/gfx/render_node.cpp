//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_node.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        void RenderNode::render(Mesh& mesh) {
            if (targets.getSize() == 0) {
                CB_CORE_WARN("Render node has no targets");
            }

            for (uint i = 0; i < sources.getSize(); i++) {
                renderer.bindTexture("source_" + sources[i].getName(), sources[i].getTexture());
            }

            for (uint i = 0; i < targets.getSize(); i++) {
                renderer.setTarget(targets[i]);
                renderer.render(mesh);
            }

            renderer.clearTextureUnits();
        }

        void RenderNode::addSource(RenderTarget& source) {
            sources.push(source);
        }
    }
}