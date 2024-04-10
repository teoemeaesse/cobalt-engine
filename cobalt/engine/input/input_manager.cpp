// Created by tomas on
// 03-12-2023

#include "engine/input/input_manager.h"

#include "core/gl/context.h"
#include "engine/input/null.h"

namespace cobalt {
    namespace engine {
        DeviceID unknownPeripheral;

        InputManager::InputManager() { unknownPeripheral = registerPeripheral<NullDevice>("Unknown"); }

        void InputManager::pollEvents() {
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

        const std::string& InputManager::peripheralToString(const DeviceID peripheral) {
            for (const auto& [name, id] : peripheralIDs) {
                if (id == peripheral) {
                    return name;
                }
            }
            return peripheralToString(unknownPeripheral);
        }
    }  // namespace engine
}  // namespace cobalt