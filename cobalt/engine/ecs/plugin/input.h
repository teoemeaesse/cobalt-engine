// Created by tomas on
// 10-02-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"
#include "core/input/input_manager.h"

namespace cobalt {
    namespace engine {
        struct InputManager : public core::ecs::Resource {
            InputManager() noexcept;

            core::input::InputManager core;
        };

        struct KeyboardState : public core::ecs::Resource {};

        class InputPlugin : public core::ecs::Plugin {
            public:
            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt