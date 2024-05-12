// Created by tomas on
// 08-12-2023

#include "engine/render/graph.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        const uint RenderGraph::addNode(Scope<RenderNode> node) {
            nodes.push_back(Move(node));
            return nodes.size() - 1;
        }

        void RenderGraph::execute(const Camera& camera) {
            for (uint i = 0; i < nodes.size(); i++) {
                for (uint j = 0; j < nodes[i]->getTargets().size(); j++) {
                    nodes[i]->getTargets()[j].getFBO().clear();
                }
            }
            for (uint i = 0; i < nodes.size(); i++) {
                nodes[i]->render(camera);
            }
        }
    }  // namespace engine
}  // namespace cobalt