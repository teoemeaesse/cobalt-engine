// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/registry.h"

#include <iostream>

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/entity.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        Entity& EntityRegistry::add(ComponentRegistry& componentRegistry) noexcept {
            EntityProperties::ID id;
            if (freeIDs.empty()) {
                id = EntityProperties::ID(entities.size());
                versions.emplace_back(1);
            } else {
                id = freeIDs.front();
                versions.at(id) = versions.at(id) == num::MAX_UINT64 ? 1 : versions.at(id) + 1;
                freeIDs.pop();
            }
            entities.erase(id);
            entities.emplace(std::piecewise_construct, std::forward_as_tuple(id),
                             std::forward_as_tuple(id, versions.at(id), *this, componentRegistry));
            return entities.at(id);
        }

        void EntityRegistry::remove(const Entity& entity) noexcept {
            if (!isAlive(entity)) {
                return;
            }
            entities.at(entity.getID()).version = 0;  // Easiest way to invalidate an entity.
            freeIDs.push(entity.getID());
        }

        void EntityRegistry::remove(const EntityProperties::ID& entityID) noexcept {
            if (entities.find(entityID) == entities.end()) {
                return;
            }
            entities.at(entityID).version = 0;  // Easiest way to invalidate an entity.
            freeIDs.push(entityID);
        }

        const bool EntityRegistry::isAlive(const Entity& entity) const noexcept {
            return entity.getVersion() != 0 && entities.find(entity.getID()) != entities.end() && entities.at(entity.getID()) == entity;
        }

        const uint64 EntityRegistry::getSize() const noexcept { return entities.size(); }
    }  // namespace core::ecs
}  // namespace cobalt