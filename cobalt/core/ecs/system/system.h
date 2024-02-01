// Created by tomas on
// 31-01-2024

#pragma once

#include "core/ecs/system/query.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Interface for all systems. Used to store systems in a vector via type erasure.
         */
        class SystemInterface {
            public:
            /**
             * @brief: Default virtual destructor.
             * @return: void
             */
            virtual ~SystemInterface() noexcept = default;

            /**
             * @brief: Runs the system.
             * @return: void
             */
            virtual void run() = 0;

            private:
            /**
             * @brief: Default constructor.
             * @return: void
             */
            SystemInterface() noexcept = default;
        };

        /**
         * @brief: System class. Used to run logic on entities with specific components.
         * @tparam Queries...: Queries to run on. Must derive from Query<...>.
         */
        template <typename... Queries>
        class System : SystemInterface {
            static_assert((std::is_base_of<QueryInterface, Queries>::value && ...), "All queries must derive from Query<...>.");

            public:
            /**
             * @brief: Creates a new system.
             * @param world: The world that the system will run on.
             * @return: A new system.
             */
            explicit System(const World& world) noexcept : world(world) {}
            /**
             * @brief: Destroys the system.
             * @return: void
             */
            virtual ~System() noexcept = default;

            /**
             * @brief: Runs the system.
             * @return: void
             */
            void run() override { runQueries(std::make_index_sequence<sizeof...(Queries)>{}); }

            /**
             * @brief: Runs the system on the given queries. Overload this function to implement custom logic.
             * @tparam Queries...: The queries to run on. Must derive from Query<...>.
             * @param queries: The queries to run on.
             * @return: void
             */
            virtual void run(Queries... queries) = 0;

            private:
            const World& world;

            /**
             * @brief: Template magic.
             * @tparam ...Is: Indices.
             * @return: void
             */
            template <size_t... Is>
            void runQueries(std::index_sequence<Is...>) {
                run(Query<std::tuple_element_t<Is, Tuple<Queries...>>>(world)...);
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt