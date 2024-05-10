/**
 * @file system.h
 * @brief A system is a function that runs logic on entities with specific components.
 * @author Tomás Marques
 * @date 31-01-2024
 */

#pragma once

#include "core/ecs/system/query.h"
#include "core/ecs/system/request.h"

namespace cobalt {
    namespace core::ecs {
        class EventManager;

        /**
         * @brief Type-erased interface for all System's.
         */
        class SystemInterface {
            public:
            /**
             * @brief Default destructor.
             */
            virtual ~SystemInterface() noexcept = default;

            /**
             * @brief Runs the system.
             */
            virtual void run() = 0;

            protected:
            /**
             * @brief Default constructor.
             */
            SystemInterface() noexcept = default;
        };

        /**
         * @brief A system consists of a function used to run logic on entities with specific components which can accept SystemParameter's as
         * arguments.
         * @tparam Params... The system parameters.
         * @see SystemParameter
         * @see Query, ReadRequest, WriteRequest, Commands
         */
        template <typename... Params>
        class System : public SystemInterface {
            static_assert((std::is_base_of<SystemParameter, Params>::value && ...), "All system parameters must derive from SystemParameter.");
            static_assert(
                (std::is_constructible<Params, EntityRegistry&, ResourceRegistry&, SystemManager&, EventManager&>::value && ...),
                "All system parameters must be constructible with an EntityRegistry, a ResourceRegistry, a SystemManager and an EventManager.");

            public:
            /**
             * @brief Creates a new System.
             * @param entityRegistry The EntityRegistry that the system will run on.
             * @param resourceRegistry The ResourceRegistry that the system will run on.
             * @param systemManager The SystemManager that owns this system.
             * @param eventManager The EventManager that the system will run on.
             */
            explicit System(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                            EventManager& eventManager) noexcept
                : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry), systemManager(systemManager), eventManager(eventManager) {}
            /**
             * @brief Default destructor.
             */
            virtual ~System() noexcept = default;

            /**
             * @brief Runs the system.
             */
            void run() override { populateParams(std::make_index_sequence<sizeof...(Params)>{}); }

            /**
             * @brief Runs the system on the given system parameters. Overload this function to implement custom logic.
             * @param params The system parameters to run on.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            virtual void run(Params... params) = 0;

            private:
            EntityRegistry& entityRegistry;      ///< The EntityRegistry that the system will run on.
            ResourceRegistry& resourceRegistry;  ///< The ResourceRegistry that the system will run on.
            SystemManager& systemManager;        ///< The SystemManager that owns this system.
            EventManager& eventManager;          ///< The EventManager that the system will run on.

            /**
             * @brief Automagically populates the system parameters.
             * @tparam Is... The indices of the system parameters.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <size_t... Is>
            void populateParams(std::index_sequence<Is...>) {
                run(std::tuple_element_t<Is, Tuple<Params...>>(entityRegistry, resourceRegistry, systemManager, eventManager)...);
            }
        };

        /**
         * @brief The LambdaSystem is a system that runs a lambda function on entities with specific components.
         * @tparam Func The lambda function type.
         * @tparam Params... The system parameters.
         * @see SystemParameter
         * @see Query, ReadRequest, WriteRequest, Commands
         */
        template <typename Func, typename... Params>
        class LambdaSystem : public System<Params...> {
            public:
            Func func;  ///< The lambda function to run.

            /**
             * @brief Creates a new System.
             * @param func The lambda function to run.
             * @param entityRegistry The EntityRegistry that the system will run on.
             * @param resourceRegistry The ResourceRegistry that the system will run on.
             * @param systemManager The SystemManager that owns this system.
             * @param eventManager The EventManager that the system will run on.
             */
            LambdaSystem(Func func, EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                         EventManager& eventManager)
                : System<Params...>(entityRegistry, resourceRegistry, systemManager, eventManager), func(func) {}

            /**
             * @brief Runs the lambda system on the given system parameters.
             * @param params The system parameters to run on.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            void run(Params... params) override { func(std::forward<Params>(params)...); }
        };
    }  // namespace core::ecs
}  // namespace cobalt