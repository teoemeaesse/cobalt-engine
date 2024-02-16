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

        void World::addResource(Scope<Resource>&& resource) noexcept { resourceRegistry.add(Move(resource)); }

        void World::startup() noexcept { systemManager.startup(); }

        void World::update() noexcept { systemManager.update(); }

        void World::render() noexcept { systemManager.render(); }

        void World::shutdown() noexcept { systemManager.shutdown(); }
    }  // namespace core::ecs
}  // namespace cobalt