// Created by tomas on
// 31-01-2024

#pragma once

#include "core/ecs/system/query.h"
#include "core/ecs/system/request.h"

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

            protected:
            /**
             * @brief: Default constructor.
             * @return: void
             */
            SystemInterface() noexcept = default;
        };

        /**
         * @brief: System class. Used to run logic on entities with specific components.
         * @tparam Params...: System parameters. Can be queries or resources.
         */
        template <typename... Params>
        class System : public SystemInterface {
            static_assert((std::is_base_of<SystemParameter, Params>::value && ...), "All system parameters must derive from SystemParameter.");
            static_assert((std::is_constructible<Params, EntityRegistry&, ResourceRegistry&>::value && ...),
                          "All system parameters must be constructible with an EntityRegistry and a ResourceRegistry.");

            public:
            /**
             * @brief: Creates a new system.
             * @param entityRegistry: The entity registry that the system will run on.
             * @param resourceRegistry: The resource registry that the system will run on.
             * @return: A new system.
             */
            explicit System(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept
                : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry) {}
            /**
             * @brief: Destroys the system.
             * @return: void
             */
            virtual ~System() noexcept = default;

            /**
             * @brief: Runs the system.
             * @return: void
             */
            void run() override { populateParams(std::make_index_sequence<sizeof...(Params)>{}); }

            /**
             * @brief: Runs the system on the given system parameters. Overload this function to implement custom logic.
             * @param params: The system parameters to run on.
             * @return: void
             */
            virtual void run(Params... params) = 0;

            private:
            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;

            /**
             * @brief: Template magic.
             * @tparam ...Is: Indices.
             * @return: void
             */
            template <size_t... Is>
            void populateParams(std::index_sequence<Is...>) {
                run(std::tuple_element_t<Is, Tuple<Params...>>(entityRegistry, resourceRegistry)...);
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt