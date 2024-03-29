// Created by tomas on
// 10-02-2024

#include "engine/ecs/plugin/input/input.h"

#include "core/ecs/system/commands.h"
#include "engine/ecs/plugin/gfx/window.h"
#include "engine/ecs/plugin/time/time.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        InputPlugin::InputPlugin() noexcept : Plugin(TITLE, "Provides input management.", WindowPlugin{}, TimePlugin{}) {}

        void InputPlugin::onPlug(core::ecs::World& world) const noexcept {
            world.addResource<core::input::InputManager>();

            /**
             * @brief: Poll input events.
             */
            world.addSystem<WriteRequest<core::input::InputManager>>(DefaultSchedules::PreUpdate, [](auto inputManager) {
                inputManager.get().pollEvents();
                inputManager.get().clearEvents();
            });
        }
    }  // namespace engine
}  // namespace cobalt