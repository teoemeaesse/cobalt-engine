// Created by tomas on
// 18-01-2024

#include "core/ecs/world.h"

namespace cobalt {
    namespace core::ecs {
        World::World() noexcept
            : entityRegistry(componentRegistry),
              componentRegistry(),
              resourceRegistry(),
              systemManager(entityRegistry, resourceRegistry, eventManager),
              eventManager(entityRegistry, resourceRegistry, systemManager) {}

        Entity& World::spawn() noexcept { return entityRegistry.add(); }

        void World::registerEvent(const std::string& name, const std::string& description) noexcept { eventManager.registerEvent(name, description); }

        void World::triggerEvent(const std::string& eventName) noexcept { eventManager.triggerEvent(eventName); }

        void World::addResource(Scope<Resource>&& resource) noexcept { resourceRegistry.add(Move(resource)); }

        bool World::isPlugin(const std::string& title) const noexcept { return pluginManager.isPlugin(title); }

        void World::startup() {
            pluginManager.checkDependencies();
            systemManager.startup();
        }

        void World::update() noexcept {
            eventManager.clearQueue();
            systemManager.update();
        }

        void World::render() noexcept { systemManager.render(); }

        void World::shutdown() noexcept { systemManager.shutdown(); }
    }  // namespace core::ecs
}  // namespace cobalt