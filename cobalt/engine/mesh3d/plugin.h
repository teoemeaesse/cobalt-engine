/**
 * @file plugin.h
 * @brief Plugin for loading 3D meshes.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "engine/mesh3d/mesh.h"

namespace cobalt {
    namespace engine {
        class Mesh3DPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Mesh 3D";

            /**
             * @brief Construct the plugin.
             */
            Mesh3DPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;

            /**
             * @brief Create a rectangle-shaped mesh.
             * @param width The width.
             * @param height The height.
             * @param material The material.
             * @return The rectangle mesh.
             */
            static Mesh createRectangle(const uint width, const uint height, Material& material);

            /**
             * @brief Create a circle-shaped mesh.
             * @param radius The radius.
             * @param material The material.
             * @return The circle mesh.
             */
            static Mesh createSphere(const uint radius, Material& material);

            /**
             * @brief Create a cube-shaped mesh.
             * @param side The cube's side.
             * @param material The material.
             * @return The cube mesh.
             */
            static Mesh createCube(const uint side, Material& material);

            /**
             * @brief Create a grid-shaped mesh.
             * @param side The grid's visible radius.
             * @param material The material.
             * @return The grid mesh.
             */
            static Mesh createGrid(const uint side, Material& material);
        };
    }  // namespace engine
}  // namespace cobalt