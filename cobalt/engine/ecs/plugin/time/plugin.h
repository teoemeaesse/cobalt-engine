// Created by tomas on
// 30-03-2024

#pragma once

#include "engine/ecs/plugin/time/time.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Time integration plugin. Provides basic time integration for linear and angular motion.
         */
        class TimePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Time";

            /**
             * @brief: Construct the plugin.
             * @return: TimePlugin
             */
            TimePlugin() noexcept : Plugin(TITLE, "Provides delta time for frame interpolation and timer support.") {}

            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override { world.addResource<Time>(); }
        };
    }  // namespace engine
}  // namespace cobalt