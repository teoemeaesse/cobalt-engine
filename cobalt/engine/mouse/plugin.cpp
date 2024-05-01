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
             * @brief Add input peripherals to the world.
             */
            world.addSystem<ecs::WriteRequest<InputManager>>(
                ecs::DefaultSchedules::Startup, [](auto inputManager) { inputManager->template registerPeripheral<Mouse>(Mouse::NAME, 1.0f); });

            /**
             * @brief Set input callbacks.
             */
            world.addSystem<ecs::WriteRequest<Window>>(ecs::DefaultSchedules::Startup, [](auto window) {
                window->setMouseButtonCallback([](InputManager& manager, const int button, const bool down) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onButtonPress(static_cast<MouseInputID>(button), down);
                    } catch (InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window->setCursorCallback([](InputManager& manager, const float xpos, const float ypos) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onMove(xpos, ypos);
                    } catch (InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
                window->setScrollCallback([](InputManager& manager, const float xoffset, const float yoffset) {
                    try {
                        manager.getPeripheral<Mouse>(Mouse::NAME).onScroll(xoffset, yoffset);
                    } catch (InvalidInputException<MouseInputID>& e) {
                        CB_CORE_ERROR(e.what());
                    } catch (PeripheralNotFoundException& e) {
                        CB_CORE_ERROR(e.what());
                    }
                });
            });
        }
    }  // namespace engine
}  // namespace cobalt