//
// Created
// by
// tomas
// on
// 03-12-2023.
//

#include "core/input/input_manager.h"

#include "core/gfx/render_context.h"

namespace cobalt {
    namespace core {
        DeviceID unknownPeripheral;

        void InputManager::pollEvents() {
            glfwPollEvents();
            for (const auto& [name, id] : peripheralIDs) {
                if (name != "Unknown") {
                    peripherals[id]->pollEvents();
                }
            }
        }

        void InputManager::clearEvents() {
            for (const auto& [name, id] : peripheralIDs) {
                if (name != "Unknown") {
                    peripherals[id]->clearEvents();
                }
            }
        }

        InputManager::InputManager() {
            unknownPeripheral = registerPeripheral<Keyboard>("Unknown");  // TODO: Create NULL peripheral type
        }

        const std::string& InputManager::peripheralToString(const DeviceID peripheral) {
            for (const auto& [name, id] : peripheralIDs) {
                if (id == peripheral) {
                    return name;
                }
            }
            return peripheralToString(unknownPeripheral);
        }
    }  // namespace core
}  // namespace
   // cobalt