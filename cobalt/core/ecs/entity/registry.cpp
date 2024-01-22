// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/registry.h"

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        EntityRegistry::EntityRegistry(ComponentRegistry& componentRegistry) noexcept : componentRegistry(componentRegistry) {}

        const Entity::ID EntityRegistry::add() noexcept {
            Entity::ID id;
            if (freeIDs.empty()) {
                id = Entity::ID(entities.size());
            } else {
                id = freeIDs.front();
                freeIDs.pop();
            }
            entities.emplace(id, Entity(id, *this, componentRegistry));
            return id;
        }

        void EntityRegistry::remove(const Entity::ID id) noexcept {
            entities.erase(id);
            freeIDs.push(id);
        }

        const bool EntityRegistry::isAlive(const Entity::ID id) const noexcept { return entities.find(id) != entities.end(); }

        const uint64 EntityRegistry::getCount() const noexcept { return entities.size(); }
    }  // namespace core::ecs
}  // namespace cobalt