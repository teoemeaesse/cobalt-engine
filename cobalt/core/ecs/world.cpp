// Created by tomas on
// 18-01-2024

#include "core/ecs/world.h"

namespace cobalt {
    namespace core::ecs {
        World::World() noexcept : entityRegistry(), componentRegistry() {}

        Entity& World::spawn() noexcept { return entityRegistry.add(componentRegistry); }

        void World::kill(const Entity& entity) noexcept {
            componentRegistry.removeAll(entity.getID());
            entityRegistry.remove(entity);
        }

        void World::update() noexcept {
            for (auto& schedule : schedules) {
                schedule.second.run();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt