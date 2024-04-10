// Created by tomas on
// 30-03-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "engine/time/time.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Time integration plugin. Provides basic time integration for linear and angular motion.
         */
        class TimePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Time";

            /**
             * @brief Construct the plugin.
             * @return TimePlugin
             */
            TimePlugin() noexcept;

            /**
             * @brief Initialize the plugin.
             * @param world World instance.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt