// Created by tomas on
// 03-12-2023

#pragma once

#include "core/exceptions/input_exception.h"
#include "core/input/input_command.h"
#include "core/input/keyboard.h"
#include "core/input/mouse.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::input {
        /** @brief: The input manager. Handles all input from peripherals such as the keyboard
         * and mouse. It then dispatches events to the appropriate listeners.
         */
        class InputManager {
            public:
            /** @brief: Create a new input manager.
             * @param mouseSensitivity: The mouse sensitivity.
             * @return: The new input manager.
             */
            InputManager();
            /** @brief: Destroy the input manager.
             */
            ~InputManager() = default;

            /** @brief: Poll all events from the peripherals.
             */
            void pollEvents();
            /** @brief: Clear all events from the peripherals.
             */
            void clearEvents();

            /** @brief: Register a peripheral to the input manager.
             * @param name: The name of the peripheral.
             * @tparam T: The type of the peripheral.
             * @tparam Args: The arguments to pass to the constructor of the peripheral.
             * @return: The new peripheral's device id.
             */
            template <typename T, typename... Args>
            const DeviceID registerPeripheral(const std::string& name, Args&&... args) {
                const DeviceID id = peripherals.size();
                Scope<InputDevice> peripheral = createScope<T>(id, std::forward<Args>(args)...);
                peripherals[peripheral->getId()] = std::move(peripheral);
                peripheralIDs[name] = id;
                return id;
            }

            /** @brief: Get the name of a peripheral, given its registered handle.
             * @param id: The peripheral's device id.
             * @return: The name of the peripheral.
             */
            const std::string& peripheralToString(const DeviceID id);

            /** @brief: Get a peripheral, given its handle.
             * @param id: The peripheral's device id.
             * @return: The peripheral.
             */
            template <typename T>
            T& getPeripheral(const DeviceID id) {
                static_assert(std::is_base_of_v<InputDevice, T>, "T must be derived from an InputDevice");
                if (peripherals.find(id) == peripherals.end()) {
                    throw PeripheralNotFoundException(peripheralToString(id));
                }
                return *static_cast<T*>(peripherals[id].get());
            }
            /** @brief: Get a peripheral, given its name.
             * @return: The peripheral.
             */
            template <typename T>
            T& getPeripheral(const std::string& name) {
                static_assert(std::is_base_of_v<InputDevice, T>, "T must be derived from an InputDevice");
                if (peripheralIDs.find(name) == peripheralIDs.end()) {
                    throw PeripheralNotFoundException(name);
                }
                return getPeripheral<T>(peripheralIDs[name]);
            }

            private:
            UMap<std::string, DeviceID> peripheralIDs;       // Map from peripheral names to peripheral ids for easy lookup.
            UMap<DeviceID, Scope<InputDevice>> peripherals;  // The peripherals.
        };
    }  // namespace core::input
}  // namespace cobalt