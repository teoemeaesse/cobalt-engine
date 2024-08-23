// Created by tomas on
// 08-12-2023

#pragma once

#include "engine/raster3d/renderer.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A render node is a node in a graph that connects source render targets to output render targets using a single renderer.
         */
        class RenderNode {
            public:
            /**
             * @brief Create a render node with a renderer.
             * @param renderer The renderer to use for rendering.
             */
            RenderNode(Raster3D& renderer);
            /**
             * @brief Destroy the render node.
             */
            virtual ~RenderNode() = default;
            /**
             * @brief Copy constructor.
             * @param other The other render node.
             * @return The render node.
             */
            RenderNode(const RenderNode&);
            /**
             * @brief Move constructor.
             * @param other The other render node.
             * @return The render node.
             */
            RenderNode(RenderNode&&) noexcept;
            /**
             * @brief Copy assignment.
             * @param other The other render node.
             * @return The render node.
             */
            RenderNode& operator=(const RenderNode&) = delete;
            /**
             * @brief Move assignment.
             * @param other The other render node.
             * @return The render node.
             */
            RenderNode& operator=(RenderNode&&) = delete;

            /**
             * @brief Render to the outputs, binding the sources to the adequate texture units. Each render node should override this method and call
             * the protected render method.
             * @param world The world to render.
             */
            virtual void render(const core::ecs::World& world) = 0;
            /**
             * @brief Called when the window is resized.
             * @param width The new width.
             * @param height The new height.
             */
            virtual void onResize(const float width, const float height) = 0;

            /**
             * @brief Add a source to the render node. It will be bound to the next available texture unit.
             * @param source The source to add.
             */
            void addSource(RenderTarget&& source);

            /**
             * @brief Add an output to the render node.
             * @param cameraID The camera to use for rendering to the output.
             * @param output The output to add.
             */
            void addOutput(const CameraID& cameraID, RenderTarget&& output);

            /**
             * @brief Get the sources.
             * @return The sources.
             */
            Vec<RenderTarget>& getSources();
            /**
             * @brief Get the outputs.
             * @return The outputs.
             */
            Vec<RenderTarget>& getOutputs();

            protected:
            Vec<RenderTarget> sources;            // The list of sources.
            Vec<RenderTarget> outputs;            // The list of outputs.
            UMap<std::string, CameraID> cameras;  // The cameras to use for each output render target.
            Raster3D& renderer;                   // The renderer to use.

            /**
             * @brief Render to the outputs, binding the sources to the respective texture units. Each render node should decide how to call this
             * method.
             * @param mesh The mesh to render.
             * @param pointLighting A UBO containing every point light in the scene.
             */
            void renderMesh(Mesh& mesh, core::gl::UBO& pointLighting);
            /**
             * @brief Render to the outputs, binding the sources to the respective texture units. Each render node should decide how to call this
             * method. Uses no lighting.
             * @param mesh The mesh to render.
             */
            void renderMesh(Mesh& mesh);
        };
    }  // namespace engine
}  // namespace cobalt