// Created by tomas on
// 02-04-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"
#include "engine/ecs/plugin/camera/manager.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Camera plugin. Provides camera control and creation.
         */
        class CameraPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Camera";

            /**
             * @brief: Construct the plugin.
             * @return: CameraPlugin
             */
            CameraPlugin() noexcept : Plugin(TITLE, "Provides camera control and creation.") {}

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override { world.addResource<CameraManager>(); }
        };
    }  // namespace engine
}  // namespace cobalt