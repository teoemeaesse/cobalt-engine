// Created by tomas on
// 21-01-2024

#include "core/ecs/component/storage.h"

namespace cobalt {
    namespace core::ecs {
        void ComponentStorage::add(const Entity::ID entityID, const Component& component) noexcept {
            entityToIndex[entityID] = components.size();
            components.push_back(component);
        }

        void ComponentStorage::remove(const Entity::ID entityID) noexcept {
            if (entityToIndex.find(entityID) == entityToIndex.end()) {
                return;
            }
            const uint64 index = entityToIndex[entityID];
            entityToIndex.erase(entityID);
            if (index != components.size() - 1) {
                components[index] = components.back();
            }
            components.pop_back();
        }

        Component& ComponentStorage::get(const Entity::ID entityID) noexcept { return components[entityToIndex[entityID]]; }

        const Component& ComponentStorage::get(const Entity::ID entityID) const noexcept { return components[entityToIndex.at(entityID)]; }
    }  // namespace core::ecs
}  // namespace cobalt