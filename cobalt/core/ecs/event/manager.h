// Created by tomas on
// 14-02-2024

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
             * @brief Default constructor.
             * @param entityRegistry Entity registry.
             * @param resourceRegistry Resource registry.
             * @param systemManager System manager.
             * @return EventManager instance.
             */
            EventManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept;
            /**
             * @brief Default destructor.
             */
            ~EventManager() noexcept = default;

            /**
             * @brief Register an event.
             * @param name Event name.
             * @param description Event description.
             * @return Event instance.
             */
            const Event& registerEvent(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief Trigger an event.
             * @param name Event name.
             */
            void triggerEvent(const std::string& name) noexcept;
            /**
             * @brief Process the event queue.
             */
            void clearQueue() noexcept;

            /**
             * @brief Hook a system to an event.
             * @tparam SystemType: System type.
             * @param eventName Event to hook into.
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                hooks.emplace(eventName, Move(CreateScope<SystemType>(entityRegistry, resourceRegistry, systemManager, *this)));
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
                hooks.emplace(eventName,
                              Move(CreateScope<LambdaSystem<Func, Params...>>(func, entityRegistry, resourceRegistry, systemManager, *this)));
            }

            private:
            UMap<std::string, Scope<SystemInterface>> hooks;
            UMap<std::string, Event> events;
            Queue<Event> eventQueue;
            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
            SystemManager& systemManager;
        };
    }  // namespace core::ecs
}  // namespace cobalt