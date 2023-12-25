//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/pch.h"
#include "core/gfx/render_node.h"
#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        class RenderGraph {
            public:
            /** Creates an empty render graph. 
             * The graph is empty, so it is not possible to render anything.
             * @return: A render graph with no nodes.
             */
            RenderGraph() = default;
            /** Destroys the render graph.
             */
            ~RenderGraph() = default;
            
            /** Adds a node to the render graph.
             * @param node: The node to add.
             * @return: The index of the node in the graph.
             */
            const uint addNode(Scope<RenderNode> node);

            /** Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             */
            virtual void onResize(const float width, const float height) = 0;
            
            /** Executes the render graph.
             */
            void execute();
            
            protected:
            Vec<Scope<RenderNode>> nodes;   // All the nodes in the graph, in topological order.
        };
    }
}