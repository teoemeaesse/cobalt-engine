// Created by tomas on
// 08-12-2023

#pragma once

#include "engine/raster3d/mesh.h"
#include "engine/raster3d/skybox.h"
#include "engine/render/plugin.h"

namespace cobalt {
    namespace engine {
        class Raster3D : public Renderer {
            public:
            /**
             * @brief Create a 3d rasterized renderer.
             */
            Raster3D() noexcept;
            /**
             * @brief Default destructor.
             */
            ~Raster3D() noexcept = default;

            /**
             * @brief Render to a target.
             * @param target The target to render to.
             */
            void render(RenderTarget& target) const override;

            /**
             * @brief Render a mesh.
             * @param mesh The mesh to render.
             * @param target The render target to render to.
             */
            void renderMesh(Mesh& mesh, RenderTarget& target) const;

            /**
             * @brief Render a skybox.
             * @param skybox The skybox to render.
             * @param target The render target to render to.
             */
            void renderSkybox(Skybox& skybox, RenderTarget& target) const;

            /**
             * @brief Load the camera data into the camera UBO.
             * @param data The camera UBO data.
             */
            void loadCameraUBO(const Camera::UBO& data) const;

            private:
            core::gl::UBO cameraUBO;  // Camera UBO.
        };
    }  // namespace engine
}  // namespace cobalt