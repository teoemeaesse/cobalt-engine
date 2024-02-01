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
             * @tparam Queries...: The queries that the system will run on. Must derive from Query<...>.
             * @param system: The system to add.
             * @return: void
             */
            template <typename... Queries>
            void addSystem(System<Queries...>&& system) noexcept {
                static_assert((std::is_base_of<QueryInterface, Queries>::value && ...), "All queries must derive from Query<...>.");
                systems.push_back(createScope<System<Queries...>>(Move(system)));
            }

            private:
            const World& world;
            const std::string name;
            Vec<Scope<SystemInterface>> systems;
        };
    }  // namespace core::ecs
}  // namespace cobalt