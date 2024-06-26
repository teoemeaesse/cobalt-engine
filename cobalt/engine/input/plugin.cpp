// Created by tomas on
// 06-04-2024

#include "engine/input/plugin.h"

#include "engine/input/input_manager.h"
#include "engine/time/plugin.h"
#include "engine/window/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        InputPlugin::InputPlugin() noexcept : Plugin(TITLE, "Provides input management.", WindowPlugin{}, TimePlugin{}) {}

        void InputPlugin::onPlug(ecs::World& world) const noexcept {
            world.addResource<InputManager>();

            world.addSystem<ecs::WriteRequest<InputManager>>(ecs::DefaultSchedules::PreUpdate, [](auto inputManager) {
                inputManager->pollEvents();
                inputManager->clearEvents();
            });
        }
    }  // namespace engine
}  // namespace cobalt