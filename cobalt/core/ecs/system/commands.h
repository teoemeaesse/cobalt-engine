/**
 * @file commands.h
 * @brief A command the user to modify the World from inside a System.
 * @author Tomás Marques
 * @date 13-02-2024
 */

#pragma once

#include "core/ecs/event/manager.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Commands allow for easy entity creation / destruction and system / resource management from a system.
         */
        class Commands : SystemParameter {
            public:
            /**
             * @brief Create a new Commands.
             * @param entityRegistry The EntityRegistry where the commands will be executed.
             * @param resourceRegistry The ResourceRegistry where the commands will be executed.
             * @param systemManager The SystemManager where the commands will be executed.
             * @param eventManager The EventManager where the commands will be executed.
             */
            Commands(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                     EventManager& eventManager) noexcept;
            /**
             * @brief Default destructor.
             */
            ~Commands() noexcept = default;

            /**
             * @brief Spawn a new Entity.
             * @return An entity handle.
             */
            Entity& spawn() noexcept;

            /**
             * @brief Add a System to the world.
             * @tparam SystemType The system type.
             * @param schedule The schedule to add the system to.
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "SystemType must be a subclass of SystemInterface.");
                systemManager.addSystem<SystemType>(schedule);
            }
            /**
             * @brief Add a System to the world.
             * @tparam Params... The lambda function parameters.
             * @tparam Func The lambda function type.
             * @param schedule The schedule to add the system to.
             * @param func The lambda function.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systemManager.addSystem<Params...>(schedule, func);
            }

            /**
             * @brief Hook a System to an event.
             * @tparam SystemType The system type.
             * @param eventName The event to hook into.
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "SystemType must be a subclass of SystemInterface.");
                eventManager.addHook<SystemType>(eventName);
            }
            /**
             * @brief Hook a System to an event.
             * @tparam Params... The lambda function parameters.
             * @tparam Func The lambda function type.
             * @param eventName The event to hook into.
             * @param func The lambda function.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <typename... Params, typename Func>
            void addHook(const std::string& eventName, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                eventManager.addHook<Params...>(eventName, func);
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt