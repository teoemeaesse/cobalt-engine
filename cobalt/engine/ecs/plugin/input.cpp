// Created by tomas on
// 10-02-2024

#include "engine/ecs/plugin/input.h"

#include "core/ecs/system/commands.h"
#include "core/gfx/window.h"
#include "core/input/input_manager.h"
#include "engine/ecs/plugin/time.h"
#include "engine/ecs/plugin/window.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        // add the window and time plugin dependencies
        InputPlugin::InputPlugin() noexcept : Plugin(Title, "Provides input management.", WindowPlugin{}, TimePlugin{}) {}

        void InputPlugin::onPlug(core::ecs::World& world) const noexcept {
            world.addResource<core::input::InputManager>();

            /**
             * @brief: Add input peripherals to the world.
             */
            world.addSystem<WriteRequest<core::input::InputManager>>(DefaultSchedules::Startup, [](auto inputManager) {
                inputManager.get().template registerPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME);
                inputManager.get().template registerPeripheral<core::input::Mouse>(core::input::Mouse::NAME, 1.0f);
            });

            /**
             * @brief: Poll input events.
             */
            world.addSystem<WriteRequest<core::input::InputManager>>(DefaultSchedules::PreUpdate, [](auto inputManager) {
                inputManager.get().pollEvents();
                inputManager.get().clearEvents();
            });

            /**
             * @brief: Set input callbacks.
             */
            world.addSystem<WriteRequest<core::gfx::Window>>(DefaultSchedules::Startup, [](auto window) {
                window.get().setKeyCallback([](core::input::InputManager& manager, const core::input::KeyboardInputID key, const bool down) {
                    try {
                        manager.getPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME).onKeyPress(key, down);
                    } catch (core::input::InvalidInputException<core::input::KeyboardInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (core::input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window.get().setMouseButtonCallback([](core::input::InputManager& manager, const core::input::MouseInputID button, const bool down) {
                    try {
                        manager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onButtonPress(button, down);
                    } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (core::input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window.get().setCursorCallback([](core::input::InputManager& manager, const float xpos, const float ypos) {
                    try {
                        manager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onMove(xpos, ypos);
                    } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (core::input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window.get().setScrollCallback([](core::input::InputManager& manager, const float xoffset, const float yoffset) {
                    try {
                        manager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onScroll(xoffset, yoffset);
                    } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (core::input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
            });
        }
    }  // namespace engine
}  // namespace cobalt