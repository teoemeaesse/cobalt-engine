// Created by tomas on
// 30-03-2024

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Euler integration plugin. Provides basic euler integration for linear and angular motion.
         */
        class EulerPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Euler integration";

            /**
             * @brief Construct the plugin.
             * @return EulerPlugin
             */
            EulerPlugin() noexcept;

            /**
             * @brief Initialize the plugin.
             * @param world World instance.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt