// Created by tomas on
// 13-02-2024

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
             * @brief: Default constructor.
             * @return: SystemRegistry instance.
             */
            SystemRegistry(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept;

            /**
             * @brief: Add a system to the registry.
             * @tparam SystemType: System type.
             * @param manager: System manager.
             * @return: void
             */
            template <typename SystemType>
            void addSystem(SystemManager& manager) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems.push_back(Move(createScope<SystemType>(entityRegistry, resourceRegistry, manager)));
            }
            /**
             * @brief: Add a system to the registry.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param manager: System manager.
             * @param func: Lambda function.
             * @return: void
             */
            template <typename... Params, typename Func>
            void addSystem(SystemManager& manager, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systems.push_back(Move(createScope<LambdaSystem<Func, Params...>>(func, entityRegistry, resourceRegistry, manager)));
            }

            /**
             * @brief: Run all systems in the registry.
             * @return: void
             */
            void run() noexcept;

            private:
            Vec<Scope<SystemInterface>> systems;
            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt