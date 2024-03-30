// Created by tomas on
// 30-03-2024

#pragma once

#include "engine/ecs/plugin/input/plugin.h"
#include "engine/ecs/plugin/keyboard/keyboard.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Keyboard input plugin. Provides general keyboard input.
         */
        class KeyboardPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Keyboard";

            /**
             * @brief: Construct the plugin.
             * @return: KeyboardPlugin
             */
            KeyboardPlugin() noexcept : Plugin(TITLE, "Provides keyboard input.", InputPlugin{}, WindowPlugin{}) {}

            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override {
                world.addSystem<core::ecs::WriteRequest<core::input::InputManager>>(core::ecs::DefaultSchedules::Startup, [](auto inputManager) {
                    inputManager.get().template registerPeripheral<Keyboard>(Keyboard::NAME);
                });

                world.addSystem<core::ecs::WriteRequest<core::gfx::Window>>(core::ecs::DefaultSchedules::Startup, [](auto window) {
                    window.get().setKeyCallback([](core::input::InputManager& manager, const int key, const bool down) {
                        try {
                            Keyboard& keyboard = manager.getPeripheral<Keyboard>(Keyboard::NAME);
                            keyboard.onKeyPress(keyboard.glfwToCobalt(key), down);
                        } catch (core::input::InvalidInputException<KeyboardInputID>& e) {
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