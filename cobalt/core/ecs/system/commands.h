// Created by tomas on
// 13-02-2024

#pragma once

#include "core/ecs/event/manager.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief ECS commands. Allows for easy entity creation / destruction and system / resource management from a system.
         */
        class Commands : SystemParameter {
            public:
            /**
             * @brief Default constructor.
             * @param entityRegistry Entity registry.
             * @param resourceRegistry Resource registry.
             * @param systemManager System manager.
             * @param eventManager Event manager.
             * @return Commands instance.
             */
            Commands(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                     EventManager& eventManager) noexcept;
            /**
             * @brief Default destructor.
             */
            ~Commands() noexcept = default;

            /**
             * @brief Spawn a new entity.
             * @return Entity instance.
             */
            Entity& spawn() noexcept;

            /**
             * @brief Add a system to the world.
             * @tparam SystemType: System type.
             * @param schedule Schedule to add the system to.
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "SystemType must be a subclass of SystemInterface.");
                systemManager.addSystem<SystemType>(schedule);
            }
            /**
             * @brief Add a system to the world.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param schedule Schedule to add the system to.
             * @param func Lambda function.
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systemManager.addSystem<Params...>(schedule, func);
            }

            /**
             * @brief Hook a system to an event.
             * @tparam SystemType: System type.
             * @param eventName Event to hook into.
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "SystemType must be a subclass of SystemInterface.");
                eventManager.addHook<SystemType>(eventName);
            }
            /**
             * @brief Hook a system to an event.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param eventName Event to hook into.
             * @param func Lambda function.
             */
            template <typename... Params, typename Func>
            void addHook(const std::string& eventName, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                eventManager.addHook<Params...>(eventName, func);
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt