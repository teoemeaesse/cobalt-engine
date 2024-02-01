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
             * @param world: The world that the schedule will run on.
             * @return: A new schedule.
             */
            explicit Schedule(const World& world) noexcept;
            /**
             * @brief: Destroys the schedule.
             * @return: void
             */
            ~Schedule() noexcept = default;

            /**
             * @brief: Adds a system to the schedule.
             * @tparam SystemType: System type.
             * @param world: The world that the system will run on.
             * @return: void
             */
            template <typename SystemType>
            void addSystem(const World& world) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems.push_back(Move(createScope<SystemType>(world)));
            }

            /**
             * @brief: Runs the schedule.
             * @return: void
             */
            void run() noexcept;

            private:
            const World& world;
            const std::string name;
            Vec<Scope<SystemInterface>> systems;
        };
    }  // namespace core::ecs
}  // namespace cobalt