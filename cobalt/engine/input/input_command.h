// Created by tomas on
// 04-12-2023

#pragma once

#include "core/ecs/world.h"

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

        /**
         * @brief: Any command to perform in reaction to an input.
         */
        class InputCommand {
            public:
            /**
             * @brief: Create a new input command.
             * @return: The new input command.
             */
            InputCommand() : input({false, false, 0.0f}) {}
            /**
             * @brief: Destroy the input command.
             */
            virtual ~InputCommand() = default;

            /**
             * @brief: Execute the command.
             * @return: void
             */
            virtual void execute() = 0;

            /**
             * @brief: Set the input value of the bound input.
             * @param input: The input value of the bound input.
             * @return: This input command.
             */
            InputCommand* withInput(InputValue input) {
                this->input = input;
                return this;
            }
            /**
             * @brief: Get the input value of the bound input.
             * @return: The input value of the bound input.
             */
            InputValue getInput() const { return input; }

            private:
            InputValue input;  // The input value of the bound input.
        };

        /**
         * @brief: Concrete input command. Executes a function on a receiver.
         * Extend this class to create a custom input command.
         * @tparam T: The type of the receiver.
         */
        template <typename T>
        class ConcreteInputCommand : public InputCommand {
            public:
            /**
             * @brief: Create a new concrete input command.
             * @param world: The ECS world instance.
             * @param target: The receiver of the command.
             * @return: The new concrete input command.
             */
            ConcreteInputCommand(core::ecs::World& world, T* target) : world(world), target(target) {}
            /**
             * @brief: Destroy the concrete input command.
             * @return: void
             */
            virtual ~ConcreteInputCommand() = default;

            /**
             * @brief: Get the ECS world instance.
             * @return: The ECS world instance.
             */
            core::ecs::World& getWorld() { return world; }
            /**
             * @brief: Get the ECS world instance.
             * @return: The ECS world instance.
             */
            const core::ecs::World& getWorld() const { return world; }
            /**
             * @brief: Get the receiver of the command.
             * @return: The receiver of the command.
             */
            T* getTarget() { return target; }
            /**
             * @brief: Get the receiver of the command.
             * @return: The receiver of the command.
             */
            const T* getTarget() const { return target; }

            private:
            core::ecs::World& world;  // The ECS world instance.
            T* target;                // The receiver of the command.
        };
    }  // namespace core::input
}  // namespace cobalt