// Created by tomas on
// 10-02-2024

#include "engine/ecs/plugin/input.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        InputManager::InputManager() noexcept : core() {}

        void InputPlugin::onPlug(core::ecs::World& world) const noexcept {
            world.addResource<InputManager>();

            /**
             * @brief: Add input peripherals to the world.
             */
            world.addSystem<WriteRequest<InputManager>>(World::DefaultSchedules::Startup, [](auto inputManager) {
                inputManager.get().core.template registerPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME);
                inputManager.get().core.template registerPeripheral<core::input::Mouse>(core::input::Mouse::NAME, 1.0f);
            });

            /**
             * @brief: Poll input events.
             */
            world.addSystem<WriteRequest<InputManager>>(World::DefaultSchedules::PreUpdate, [](auto inputManager) {
                inputManager.get().core.pollEvents();
                inputManager.get().core.clearEvents();
            });
        }
    }  // namespace engine
}  // namespace cobalt