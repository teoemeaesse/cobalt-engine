// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/registry.h"

#include "core/ecs/entity/entity.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        EntityRegistry::EntityRegistry(ComponentRegistry& componentRegistry) noexcept : componentRegistry(componentRegistry) {}

        Entity& EntityRegistry::add() noexcept {
            Entity::ID id;
            if (freeIDs.empty()) {
                id = Entity::ID(entities.size());
            } else {
                id = freeIDs.front();
                freeIDs.pop();
            }
            entities.emplace(id, Entity(id, *this, componentRegistry));
            return entities.at(id);
        }

        void EntityRegistry::remove(Entity& entity) noexcept {
            entities.erase(entity.getID());
            freeIDs.push(entity.getID());
        }

        const bool EntityRegistry::isAlive(const Entity& entity) const noexcept { return entities.find(entity.getID()) != entities.end(); }

        const uint64 EntityRegistry::getCount() const noexcept { return entities.size(); }
    }  // namespace core::ecs
}  // namespace cobalt