//
// Created by tomas on 27-12-2023.
//

#include "core/input/keycodes.h"


namespace cobalt {
    namespace core {
        Scope<KeyCodes> KeyCodes::instance = nullptr;
        KeyCodes::PeripheralID unknownPeripheral;

        void KeyCodes::init() {
            instance = std::make_unique<KeyCodes>();
            unknownPeripheral = registerPeripheral("Unknown");
        }

        const KeyCodes::PeripheralID KeyCodes::registerPeripheral(const std::string& name) {
            if (!instance) {
                CB_CORE_ERROR("KeyCodes not initialized before registering peripheral {0}", name);
            }
            instance->peripheralIDs[name] = instance->peripheralIDs.size();
            return instance->peripheralIDs[name];
        }

        const std::string& KeyCodes::peripheralToString(const PeripheralID peripheral) {
            for (const auto& [name, id] : instance->peripheralIDs) {
                if (id == peripheral) {
                    return name;
                }
            }
            return peripheralToString(unknownPeripheral);
        }
    }
}