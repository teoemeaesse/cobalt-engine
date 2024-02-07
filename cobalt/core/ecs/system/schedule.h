// Created by tomas on
// 31-01-2024

#pragma once

#include "core/ecs/system/system.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: A schedule is a collection of systems that are run in order.
         */
        class Schedule {
            public:
            /**
             * @brief: Creates a new schedule.
             * @param entityRegistry: The entity registry that the schedule will run on.
             * @param resourceRegistry: The resource registry that the schedule will run on.
             * @return: A new schedule.
             */
            Schedule(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept;
            /**
             * @brief: Destroys the schedule.
             * @return: void
             */
            ~Schedule() noexcept = default;

            /**
             * @brief: Adds a system to the schedule.
             * @tparam SystemType: System type.
             * @return: void
             */
            template <typename SystemType>
            void addSystem() noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems.push_back(Move(createScope<SystemType>(entityRegistry, resourceRegistry)));
            }
            /**
             * @brief: Makes a system from a lambda function.
             * @tparam Params...: The lambda function parameters.
             * @tparam Func: The lambda function type.
             * @param func: The lambda function.
             * @return: A new system.
             */
            template <typename... Params, typename Func>
            void addSystem(Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systems.push_back(Move(createScope<LambdaSystem<Func, Params...>>(func, entityRegistry, resourceRegistry)));
            }

            /**
             * @brief: Runs the schedule.
             * @return: void
             */
            void run() noexcept;

            private:
            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
            const std::string name;
            Vec<Scope<SystemInterface>> systems;
        };
    }  // namespace core::ecs
}  // namespace cobalt