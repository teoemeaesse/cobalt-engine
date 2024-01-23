// Created by tomas on
// 18-01-2024

#include "core/ecs/world.h"

namespace cobalt {
    namespace core::ecs {
        World::World() noexcept : entityRegistry(), componentRegistry() {}

        Entity& World::createEntity() noexcept { return entityRegistry.add(componentRegistry); }

        void World::destroyEntity(const Entity& entity) noexcept { entityRegistry.remove(entity); }
    }  // namespace core::ecs
}  // namespace cobalt