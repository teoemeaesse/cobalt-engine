// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        const Entity::ID EntityRegistry::createEntity() noexcept {
            Entity::ID id;
            if (freeIDs.empty()) {
                id = Entity::ID(entities.size());
            } else {
                id = freeIDs.front();
                freeIDs.pop();
            }
            entities.emplace(id, Entity(id));
            return id;
        }

        void EntityRegistry::destroyEntity(const Entity::ID id) noexcept {
            entities.erase(id);
            freeIDs.push(id);
        }

        const bool EntityRegistry::isAlive(const Entity::ID id) const noexcept { return entities.find(id) != entities.end(); }

        const uint64 EntityRegistry::getEntityCount() const noexcept { return entities.size(); }
    }  // namespace core::ecs
}  // namespace cobalt