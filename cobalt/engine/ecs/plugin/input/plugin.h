// Created by tomas on
// 10-02-2024

#pragma once

#include "core/ecs/system/commands.h"
#include "engine/ecs/plugin/time/plugin.h"
#include "engine/ecs/plugin/window/plugin.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Input plugin. Provides peripheral input state information.
         */
        class InputPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Input";

            /**
             * @brief: Construct the plugin.
             * @return: InputPlugin
             */
            InputPlugin() noexcept : Plugin(TITLE, "Provides input management.", WindowPlugin{}, TimePlugin{}) {}

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override {
                world.addResource<core::input::InputManager>();

                /**
                 * @brief: Poll input events.
                 */
                world.addSystem<core::ecs::WriteRequest<core::input::InputManager>>(core::ecs::DefaultSchedules::PreUpdate, [](auto inputManager) {
                    inputManager.get().pollEvents();
                    inputManager.get().clearEvents();
                });
            }
        };
    }  // namespace engine
}  // namespace cobalt