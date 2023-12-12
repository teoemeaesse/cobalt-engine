//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/containers/vector.h"
#include "core/gfx/render_node.h"
#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        class RenderGraph {
            public:
            /* Creates an empty render graph. 
             * The graph is empty, so it is not possible to render anything.
             * @return: A render graph with no nodes.
             */
            RenderGraph();
            /* Destroys the render graph.
             */
            ~RenderGraph() = default;

            /* Adds a node to the render graph.
             * @param node: The node to add.
             * @return: The index of the node in the graph.
             */
            const uint addNode(RenderNode&& node);
            
            /* Executes the render graph.
             */
            void execute();
            
            private:
            Vector<RenderNode> nodes;   // All the nodes in the graph, in topological order.
        };
    }
}