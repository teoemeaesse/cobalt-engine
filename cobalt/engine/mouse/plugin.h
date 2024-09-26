// Created by tomas on
// 30-03-2024

#pragma once

#include "engine/mouse/mouse.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Mouse input plugin. Provides general mouse input.
         */
        class MousePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Mouse";

            /**
             * @brief Construct the plugin.
             * @return MousePlugin
             */
            MousePlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt