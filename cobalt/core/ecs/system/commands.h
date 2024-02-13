// Created by tomas on
// 13-02-2024

#pragma once

#include "core/ecs/entity/registry.h"
#include "core/ecs/resource/registry.h"
#include "core/ecs/system/manager.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: ECS commands. Allows for easy entity creation / destruction and system / resource management from a system.
         */
        class Commands : SystemParameter {
            public:
            /**
             * @brief: Default constructor.
             * @param entityRegistry: Entity registry.
             * @param resourceRegistry: Resource registry.
             * @param systemManager: System manager.
             * @return: Commands instance.
             */
            Commands(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept;
            /**
             * @brief: Default destructor.
             * @return: void
             */
            ~Commands() noexcept = default;

            /**
             * @brief: Spawn a new entity.
             * @return: Entity instance.
             */
            Entity& spawn() noexcept;

            /**
             * @brief: Add a system to the world.
             * @tparam SystemType: System type.
             * @param schedule: Schedule to add the system to.
             * @return: void
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systemManager.addSystem<SystemType>(schedule);
            }
            /**
             * @brief: Add a system to the world.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param schedule: Schedule to add the system to.
             * @param func: Lambda function.
             * @return: void
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systemManager.addSystem<Params...>(schedule, func);
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt