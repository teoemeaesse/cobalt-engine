//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_graph.h"
#include "core/gfx/render_context.h"


namespace cobalt {
    namespace core {
        const uint RenderGraph::addNode(Scope<RenderNode> node) {
            nodes.push_back(std::move(node));
            return nodes.size() - 1;
        }

        void RenderGraph::execute() {
            for (uint i = 0; i < nodes.size(); i++) {
                for (uint j = 0; j < nodes[i]->getTargets().size(); j++) {
                    nodes[i]->getTargets()[j].getFBO().clear();
                }
            }
            for (uint i = 0; i < nodes.size(); i++) {
                nodes[i]->render();
            }
        }
    }
}