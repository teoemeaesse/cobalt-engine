/**
 * @file plugin.h
 * @brief A lighting plugin to add lighting to a scene.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#pragma once

#include "engine/lighting/point_light.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A lighting plugin to add lighting to a scene. Features point lights, TODO: directional lights and spotlights.
         * This plugin gathers all the lights in the world into a single structure in the post-update stage, and then uses that structure to
         * generate a lighting UBO in the pre-render stage.
         */
        class LightingPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Lighting";

            static inline constexpr const uint MAX_POINT_LIGHTS = 16;  ///< Maximum number of simultaneous point lights in the scene.

            /**
             * @brief Construct the plugin.
             */
            LightingPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt