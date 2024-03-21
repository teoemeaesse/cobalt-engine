// Created by tomas on
// 10-02-2024

#pragma once

#include "core/ecs/world.h"

namespace cobalt {
    namespace engine {
        struct KeyboardState : public core::ecs::Resource {};

        /**
         * @brief: Input plugin. Provides peripheral input state information.
         */
        class InputPlugin : public core::ecs::Plugin {
            public:
            /**
             * @brief: Construct the plugin.
             * @return: InputPlugin
             */
            InputPlugin() noexcept;

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt