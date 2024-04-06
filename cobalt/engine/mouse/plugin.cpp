// Created by tomas on
// 06-04-2024

#include "engine/mouse/plugin.h"

#include "engine/input/plugin.h"
#include "engine/window/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        MousePlugin::MousePlugin() noexcept : Plugin(TITLE, "Provides mouse input.", InputPlugin{}, WindowPlugin{}) {}

        void MousePlugin::onPlug(ecs::World& world) const noexcept {
            /**
             * @brief: Add input peripherals to the world.
             */
            world.addSystem<ecs::WriteRequest<input::InputManager>>(
                ecs::DefaultSchedules::Startup, [](auto inputManager) { inputManager.get().template registerPeripheral<Mouse>(Mouse::NAME, 1.0f); });

            /**
             * @brief: Set input callbacks.
             */
            world.addSystem<ecs::WriteRequest<gfx::Window>>(ecs::DefaultSchedules::Startup, [](auto window) {
                window.get().setMouseButtonCallback([](input::InputManager& manager, const int button, const bool down) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onButtonPress(static_cast<MouseInputID>(button), down);
                    } catch (input::InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window.get().setCursorCallback([](input::InputManager& manager, const float xpos, const float ypos) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onMove(xpos, ypos);
                    } catch (input::InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window.get().setScrollCallback([](input::InputManager& manager, const float xoffset, const float yoffset) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onScroll(xoffset, yoffset);
                    } catch (input::InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (input::PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
            });
        }
    }  // namespace engine
}  // namespace cobalt