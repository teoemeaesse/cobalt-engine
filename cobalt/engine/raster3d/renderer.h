// Created by tomas on
// 08-12-2023

#pragma once

#include "engine/mesh3d/mesh.h"
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
             * @brief Immediately renders a mesh to a target.
             * @param mesh The mesh to render.
             * @param pointLighting The point lights to illuminate the scene with.
             */
            void render(Mesh& mesh, core::gl::UBO& pointLighting) const override;

            /**
             * @brief Immediately renders a mesh to a target, no lighting.
             * @param mesh The mesh to render.
             */
            void render(Mesh& mesh) const override;
        };
    }  // namespace engine
}  // namespace cobalt