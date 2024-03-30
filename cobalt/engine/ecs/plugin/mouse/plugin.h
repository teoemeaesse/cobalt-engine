// Created by tomas on
// 30-03-2024

#pragma once

#include "engine/ecs/plugin/input/plugin.h"
#include "engine/ecs/plugin/mouse/mouse.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Mouse input plugin. Provides general mouse input.
         */
        class MousePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Mouse";

            /**
             * @brief: Construct the plugin.
             * @return: MousePlugin
             */
            MousePlugin() noexcept : Plugin(TITLE, "Provides mouse input.", InputPlugin{}, WindowPlugin{}) {}

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override {
                /**
                 * @brief: Add input peripherals to the world.
                 */
                world.addSystem<core::ecs::WriteRequest<core::input::InputManager>>(core::ecs::DefaultSchedules::Startup, [](auto inputManager) {
                    inputManager.get().template registerPeripheral<Mouse>(Mouse::NAME, 1.0f);
                });

                /**
                 * @brief: Set input callbacks.
                 */
                world.addSystem<core::ecs::WriteRequest<core::gfx::Window>>(core::ecs::DefaultSchedules::Startup, [](auto window) {
                    window.get().setMouseButtonCallback([](core::input::InputManager& manager, const int button, const bool down) {
                        try {
                            manager.getPeripheral<Mouse>(Mouse::NAME).onButtonPress(static_cast<MouseInputID>(button), down);
                        } catch (core::input::InvalidInputException<MouseInputID>& e) {
                            CB_CORE_ERROR(e.what());
                        } catch (core::input::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR(e.what());
                        }
                    });
                    window.get().setCursorCallback([](core::input::InputManager& manager, const float xpos, const float ypos) {
                        try {
                            manager.getPeripheral<Mouse>(Mouse::NAME).onMove(xpos, ypos);
                        } catch (core::input::InvalidInputException<MouseInputID>& e) {
                            CB_CORE_ERROR(e.what());
                        } catch (core::input::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR(e.what());
                        }
                    });
                    window.get().setScrollCallback([](core::input::InputManager& manager, const float xoffset, const float yoffset) {
                        try {
                            manager.getPeripheral<Mouse>(Mouse::NAME).onScroll(xoffset, yoffset);
                        } catch (core::input::InvalidInputException<MouseInputID>& e) {
                            CB_CORE_ERROR(e.what());
                        } catch (core::input::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR(e.what());
                        }
                    });
                });
            }
        };
    }  // namespace engine
}  // namespace cobalt