// Created by tomas on
// 08-12-2023

#pragma once

#include "core/ecs/resource/resource.h"
#include "engine/render/node.h"
#include "engine/scene/scene.h"

namespace cobalt {
    namespace engine {
        class RenderGraph : public core::ecs::Resource {
            public:
            /**
             * @brief: Destroys the render graph.
             */
            ~RenderGraph() = default;

            /**
             * @brief: Adds a node to the render graph.
             * @param node: The node to add.
             * @return: The index of the node in the graph.
             */
            const uint addNode(Scope<RenderNode> node);

            /**
             * @brief: Called upon window resize.
             * @param width: The new width of the render graph.
             * @param height: The new height of the render graph.
             * @return: void
             */
            virtual void onResize(const uint width, const uint height) = 0;

            /**
             * @brief: Executes the render graph.
             * @return: void
             */
            void execute();

            protected:
            Vec<Scope<RenderNode>> nodes;  // All the nodes in the graph, in topological order.

            /**
             * @brief: Creates an empty render graph. The graph is empty, so it is not possible to render anything.
             * @return: A render graph with no nodes.
             */
            RenderGraph() = default;
        };
    }  // namespace engine
}  // namespace cobalt