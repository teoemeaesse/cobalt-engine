//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_graph.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        RenderGraph::RenderGraph() : nodes(2) {
        }

        const uint RenderGraph::addNode(std::unique_ptr<RenderNode> node) {
            nodes.push(std::move(node));
            return nodes.getSize() - 1;
        }

        void RenderGraph::execute() {
            for (uint i = 0; i < nodes.getSize(); i++) {
                nodes[i]->render();
            }
        }
    }
}