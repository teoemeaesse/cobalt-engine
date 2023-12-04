//
// Created by tomas on 04-12-2023.
//

#pragma once


namespace cobalt {
    namespace core {
        struct InputValue {
            bool active;    // Whether the input is active.
            bool held;      // Whether the input is held.
            float value;    // The value of the input.
                            // Should be 0.0f if the input is not active.
                            // If the input is a boolean, should be 1.0f if the input is pressed and 0.0f otherwise.
                            // For axis inputs, should be the value of the axis.
        };

        /* Any command to perform in reaction to an input.
         */
        class InputCommand {
            public:
            /* Create a new input command.
             * @return: The new input command.
             */
            InputCommand() = default;
            /* Destroy the input command.
             */
            virtual ~InputCommand() = default;

            /* Execute the command.
             ^ @param input: The input value of the bound input.
             */
            virtual void execute(InputValue input) const = 0;
        };

        /* Concrete input command. Executes a function on a receiver.
         * Extend this class to create a new concrete input command.
         * @tparam T: The type of the receiver.
         */
        template <typename T>
        class ConcreteInputCommand : public InputCommand {
            public:
            /* Create a new concrete input command.
             * @param target: The receiver of the command.
             * @return: The new concrete input command.
             */
            ConcreteInputCommand(T* target) : target(target) {}
            /* Destroy the concrete input command.
             */
            virtual ~ConcreteInputCommand() = default;

            /* Get the receiver of the command.
             * @return: The receiver of the command.
             */
            T* getTarget() const {
                return target;
            }

            private:
            T* target;  // The receiver of the command.
        };
    }
}