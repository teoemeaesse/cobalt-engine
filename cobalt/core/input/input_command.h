//
// Created
// by
// tomas
// on
// 04-12-2023.
//

#pragma once

namespace cobalt {
    namespace core::input {
        struct InputValue {
            bool active;  // Whether the input is active.
            bool held;    // Whether the input is held.
            float value;  // The value of the input.
                          // Should be 0.0f if the input is not active.
                          // If the input is a boolean, should be 1.0f if the input is
                          // pressed and 0.0f otherwise. For axis inputs, should be the
                          // value of the axis.
        };

        /** @brief: Any command to perform in reaction to an input.
         */
        class InputCommand {
            public:
            /** @brief: Create a new input command.
             * @return: The new input command.
             */
            InputCommand() = default;
            /** @brief: Destroy the input command.
             */
            virtual ~InputCommand() = default;

            /** @brief: Execute the command.
             */
            virtual void execute() const = 0;

            /** @brief: Set the input value of the bound input.
             * @param input: The input value of the bound input.
             * @return: This input command.
             */
            const InputCommand* withInput(InputValue input) {
                this->input = input;
                return this;
            }
            /** @brief: Get the input value of the bound input.
             * @return: The input value of the bound input.
             */
            InputValue getInput() const { return input; }

            private:
            InputValue input;  // The input value of the bound input.
        };

        /** @brief: Concrete input command. Executes a function on a receiver.
         * Extend this class to create a new concrete input command.
         * @tparam T: The type of the receiver.
         */
        template <typename T>
        class ConcreteInputCommand : public InputCommand {
            public:
            /** @brief: Create a new concrete input command.
             * @param target: The receiver of the command.
             * @return: The new concrete input command.
             */
            ConcreteInputCommand(T* target) : target(target) {}
            /** @brief: Destroy the concrete input command.
             */
            virtual ~ConcreteInputCommand() = default;

            /** @brief: Get the receiver of the command.
             * @return: The receiver of the command.
             */
            T* getTarget() const { return target; }

            private:
            T* target;  // The receiver of the command.
        };
    }  // namespace core
} // namespace cobalt