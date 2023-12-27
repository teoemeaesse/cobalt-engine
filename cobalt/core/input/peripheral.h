//
// Created by tomas on 04-12-2023.
//

#pragma once

#include "core/input/input_command.h"
#include "core/input/keycodes.h"


namespace cobalt {
    namespace core {
        template <typename T>
        class PeripheralInput {
            static_assert(std::is_enum<T>::value, "T must be an enum class");
            
            public:
            bool operator==(const PeripheralInput<T>& other) const {
                return id == other.id;
            }
            /** Create a new peripheral input.
             * @return: The new peripheral input.
             */
            PeripheralInput() = default;
            /** Create a new peripheral input.
             * @param id: The id of the peripheral input.
             * @return: The new peripheral input.
             */
            PeripheralInput(const T id) : id(id) {}
            /** Destroy the peripheral input.
             */
            ~PeripheralInput() = default;

            /** Get the id of the peripheral input.
             * @return: The id of the peripheral input.
             */
            T getId() const {
                return id;
            }

            private:
            T id;   // The id of the peripheral input.
        };

        /** A peripheral is an input device such as a keyboard or mouse.
         * @tparam T: The type of peripheral input that commands can be bound to.
         */
        template <typename T>
        class Peripheral {
            public:
            /** Create a new peripheral.
             * @param name: The name of the peripheral.
             * @return: The new peripheral.
             */
            Peripheral(const std::string& name) : bindings() {
                id = KeyCodes::registerPeripheral(name);
            }
            /** Destroy the peripheral.
             */
            ~Peripheral() {
                for (auto& binding : bindings) {
                    binding.second.reset();
                }
            }

            /** Poll the peripheral for events.
             */
            virtual void pollEvents() = 0;
            /** Clear all queued events from the peripheral.
             */
            virtual void clearEvents() = 0;

            /** Bind a command to an input.
             * @param input: The input to bind the command to.
             * @param command: The command to bind.
             */
            void bind(const PeripheralInput<T> input, Scope<InputCommand> command) {
                bindings[input] = std::move(command);
            }

            /** Get the string representation of the peripheral.
             * @return: The string representation of the peripheral.
             */
            virtual const std::string& toString() const = 0;
            /** Convert a GLFW key code to a Cobalt key code.
             * @param glfwCode: The GLFW key code.
             * @return: The Cobalt key code.
             */
            virtual const T glfwToCobalt(const int glfwCode) const = 0;
            /** Convert a Cobalt key code to a GLFW key code.
             * @param cobaltCode: The Cobalt key code.
             * @return: The GLFW key code.
             */
            virtual const int cobaltToGlfw(const T cobaltCode) const = 0;
            /** Convert a Cobalt key code to a user-friendly string.
             * @param cobaltCode: The Cobalt key code.
             * @return: The converted string.
             */
            virtual const std::string& cobaltToStr(const T cobaltCode) const = 0;

            protected:
            Queue<const InputCommand*> events;                      // The events to execute.
            UMap<PeripheralInput<T>, Scope<InputCommand>> bindings; // The bindings for the peripheral.
            KeyCodes::PeripheralID id;                              // The id of the peripheral.
        };
    }
}

namespace std {
    template <typename T>
    struct hash<cobalt::core::PeripheralInput<T>> {
        std::size_t operator()(const cobalt::core::PeripheralInput<T>& input) const {
            return hash<T>()(input.getId());
        }
    };
}