/**
 * @file plugin.h
 * @brief Plugin for loading 3D meshes.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace engine {
        class Mesh3DPlugin : core::ecs::Plugin {
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
        };
    }  // namespace engine
}  // namespace cobalt