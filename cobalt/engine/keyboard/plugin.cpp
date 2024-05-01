// Created by tomas on
// 06-04-2024

#include "engine/input/plugin.h"

#include "engine/keyboard/plugin.h"
#include "engine/window/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        KeyboardPlugin::KeyboardPlugin() noexcept : Plugin(TITLE, "Provides keyboard input.", InputPlugin{}, WindowPlugin{}) {}

        void KeyboardPlugin::onPlug(ecs::World& world) const noexcept {
            world.addSystem<ecs::WriteRequest<InputManager>>(
                ecs::DefaultSchedules::Startup, [](auto inputManager) { inputManager->template registerPeripheral<Keyboard>(Keyboard::NAME); });

            world.addSystem<ecs::WriteRequest<Window>>(ecs::DefaultSchedules::Startup, [](auto window) {
                window->setKeyCallback([](InputManager& manager, const int key, const bool down) {
                    try {
                        Keyboard& keyboard = manager.getPeripheral<Keyboard>(Keyboard::NAME);
                        keyboard.onKeyPress(keyboard.glfwToCobalt(key), down);
                    } catch (InvalidInputException<KeyboardInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
            });
        }
    }  // namespace engine
}  // namespace cobalt