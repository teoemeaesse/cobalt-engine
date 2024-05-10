/**
 * @file manager.cpp
 * @brief An Event manager is responsible for managing events and their associated systems. It allows for the management of events and the hooking of
 * systems to events.
 * @author Tomás Marques
 * @date 14-02-2024
 */

#include "core/ecs/event/manager.h"

namespace cobalt {
    namespace core::ecs {
        EventManager::EventManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept
            : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry), systemManager(systemManager) {}

        const Event& EventManager::registerEvent(const std::string& name, const std::string& description) noexcept {
            events.emplace(name, Event(name, description));
            return events.at(name);
        }

        void EventManager::triggerEvent(const std::string& name) noexcept {
            if (events.find(name) == events.end()) {
                CB_CORE_WARN("Event {0} does not exist", name);
                return;
            }
            eventQueue.push(events.at(name));
        }

        void EventManager::clearQueue() noexcept {
            while (!eventQueue.empty()) {
                Event event = eventQueue.front();
                if (hooks.find(event.getName()) != hooks.end()) {
                    hooks.at(event.getName())->run();
                }
                eventQueue.pop();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt