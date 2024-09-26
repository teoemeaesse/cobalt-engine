// Created by tomas on
// 10-02-2024

#pragma once

#include "engine/input/input_manager.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief Input plugin. Provides peripheral input state information.
         */
        class InputPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Input";

            /**
             * @brief Construct the plugin.
             * @return InputPlugin
             */
            InputPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt