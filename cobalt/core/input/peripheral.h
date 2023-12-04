//
// Created by tomas on 04-12-2023.
//

#pragma once

#include <unordered_map>

#include "core/containers/queue.h"
#include "core/input/input_command.h"


namespace cobalt {
    namespace core {
        template <typename T>
        class PeripheralInput {
            static_assert(std::is_enum<T>::value, "T must be an enum class");

            public:
            /* Create a new peripheral input.
             * @return: The new peripheral input.
             */
            PeripheralInput() = default;
            /* Create a new peripheral input.
             * @param id: The id of the peripheral input.
             * @return: The new peripheral input.
             */
            PeripheralInput(const T id) : id(id) {}
            /* Destroy the peripheral input.
             */
            ~PeripheralInput() = default;

            /* Get the id of the peripheral input.
             * @return: The id of the peripheral input.
             */
            T getId() const {
                return id;
            }

            private:
            T id;   // The id of the peripheral input.
        };

        /* A peripheral is an input device such as a keyboard or mouse.
         * @tparam T: The type of peripheral input that commands can be bound to.
         */
        template <typename T>
        class Peripheral {
            public:
            /* Create a new peripheral.
             * @return: The new peripheral.
             */
            Peripheral() : events(16), bindings() {}
            /* Destroy the peripheral.
             */
            virtual ~Peripheral() = default;

            /* Poll the peripheral for events.
             */
            virtual void pollEvents() = 0;
            /* Clear all queued events from the peripheral.
             */
            virtual void clearEvents() = 0;

            /* Bind a command to an input.
             * @param input: The input to bind the command to.
             * @param command: The command to bind.
             */
            void bind(const PeripheralInput<T> input, std::shared_ptr<InputCommand> command) {
                bindings[input] = std::move(command);
            }

            protected:
            Queue<std::shared_ptr<const InputCommand>> events;                                    // The events to execute.
            
            private:
            std::unordered_map<PeripheralInput<T>, std::shared_ptr<InputCommand>> bindings;  // The bindings for the peripheral.
        };
    }
}

namespace std {
    template <typename T>
    struct hash<cobalt::core::PeripheralInput<T>> {
        std::size_t operator()(const cobalt::core::PeripheralInput<T>& input) const {
            return std::hash<T>()(input.getId());
        }
    };
}