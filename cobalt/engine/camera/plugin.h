// Created by tomas on
// 02-04-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "engine/camera/manager.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Camera plugin. Provides camera control and creation.
         */
        class CameraPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Camera";

            /**
             * @brief Construct the plugin.
             * @return CameraPlugin
             */
            CameraPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt