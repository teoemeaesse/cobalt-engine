// Created by tomas on
// 08-02-2024

#pragma once

#include "core/ecs/world.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Time resource.
         * @param deltaTime: Time since last frame (seconds).
         * @param elapsedTime: Time since application startup (seconds).
         */
        struct Time : public core::ecs::Resource {
            Time() noexcept;

            float deltaTime;
            float elapsedTime;
        };

        /**
         * @brief: Time plugin. Adds the Time resource to the world.
         */
        class TimePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Time";

            /**
             * @brief: Construct the plugin.
             * @return: TimePlugin
             */
            TimePlugin() noexcept;

            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt