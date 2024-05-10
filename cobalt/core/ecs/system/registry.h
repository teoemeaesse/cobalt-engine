/**
 * @file registry.h
 * @brief Storage for every system in the ECS.
 * @author Tomás Marques
 * @date 13-02-2024
 */

#pragma once

#include "core/ecs/system/system.h"

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ResourceRegistry;
        class SystemManager;

        class SystemRegistry {
            public:
            /**
             * @brief Creates a new SystemRegistry.
             * @param entityRegistry The EntityRegistry that the systems will run on.
             * @param resourceRegistry The ResourceRegistry that the systems will run on.
             * @param systemManager The SystemManager that owns this registry.
             * @param eventManager The EventManager that the systems will run on.
             */
            SystemRegistry(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                           EventManager& eventManager) noexcept;

            /**
             * @brief Adds a System (lambda function) to the registry.
             * @tparam SystemType The system type.
             */
            template <typename SystemType>
            void addSystem() noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems.push_back(Move(CreateScope<SystemType>(entityRegistry, resourceRegistry, systemManager, eventManager)));
            }
            /**
             * @brief Adds a System (lambda function) to the registry.
             * @tparam Params... The lambda function parameters.
             * @tparam Func The lambda function type.
             * @param func The lambda function.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <typename... Params, typename Func>
            void addSystem(Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systems.push_back(
                    Move(CreateScope<LambdaSystem<Func, Params...>>(func, entityRegistry, resourceRegistry, systemManager, eventManager)));
            }

            /**
             * @brief Runs all the systems in the registry.
             */
            void run() noexcept;

            private:
            Vec<Scope<SystemInterface>> systems;  ///< The stored systems.
            EntityRegistry& entityRegistry;       ///< The EntityRegistry that the systems will run on.
            ResourceRegistry& resourceRegistry;   ///< The ResourceRegistry that the systems will run on.
            SystemManager& systemManager;         ///< The SystemManager that owns this registry.
            EventManager& eventManager;           ///< The EventManager that the systems will run on.
        };
    }  // namespace core::ecs
}  // namespace cobalt