/**
 * @file manager.h
 * @brief An Event manager is responsible for managing events and their associated systems. It allows for the management of events and the hooking of
 * systems to events.
 * @author Tomás Marques
 * @date 14-02-2024
 */

#pragma once

#include "core/ecs/event/event.h"
#include "core/ecs/system/manager.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief The event manager is responsible for managing events and their associated systems.
         */
        class EventManager {
            public:
            /**
             * @brief Construct a new EventManager.
             * @param entityRegistry Entity registry.
             * @param resourceRegistry Resource registry.
             * @param systemManager System manager.
             */
            EventManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept;
            /**
             * @brief Default destructor.
             */
            ~EventManager() noexcept = default;

            /**
             * @brief Register an Event.
             * @param name The event's name.
             * @param description The event's description.
             * @return An Event handle.
             */
            const Event& registerEvent(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief Trigger an Event.
             * @param name The event's name.
             */
            void triggerEvent(const std::string& name) noexcept;
            /**
             * @brief Process the Event queue.
             */
            void clearQueue() noexcept;

            /**
             * @brief Hook a system to an Event.
             * @tparam SystemType The system type.
             * @param eventName The Event to hook into.
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                hooks.emplace(eventName, Move(CreateScope<SystemType>(entityRegistry, resourceRegistry, systemManager, *this)));
            }
            /**
             * @brief Hook a system to an event.
             * @tparam Params... The lambda function parameters.
             * @tparam Func The lambda function type.
             * @param eventName The Event to hook into.
             * @param func The lambda function.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <typename... Params, typename Func>
            void addHook(const std::string& eventName, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                hooks.emplace(eventName,
                              Move(CreateScope<LambdaSystem<Func, Params...>>(func, entityRegistry, resourceRegistry, systemManager, *this)));
            }

            private:
            UMap<std::string, Scope<SystemInterface>> hooks;  ///< All event hooks.
            UMap<std::string, Event> events;                  ///< All registered events.
            Queue<Event> eventQueue;                          ///< The event queue.
            EntityRegistry& entityRegistry;                   ///< The entity registry to operate on.
            ResourceRegistry& resourceRegistry;               ///< The resource registry to operate on.
            SystemManager& systemManager;                     ///< The system manager to operate on.
        };
    }  // namespace core::ecs
}  // namespace cobalt