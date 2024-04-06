// Created by tomas on
// 30-03-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "engine/keyboard/keyboard.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Keyboard input plugin. Provides general keyboard input.
         */
        class KeyboardPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Keyboard";

            /**
             * @brief: Construct the plugin.
             * @return: KeyboardPlugin
             */
            KeyboardPlugin() noexcept;

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt