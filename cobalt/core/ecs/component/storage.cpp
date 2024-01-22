// Created by tomas on
// 21-01-2024

#include "core/ecs/component/storage.h"

namespace cobalt {
    namespace core::ecs {
        void ComponentStorage::add(const Entity& entity, const Component& component) noexcept {
            if (entityToIndex.find(entity.getID()) != entityToIndex.end()) {
                return;
            }
            entityToIndex[entity.getID()] = components.size();
            components.push_back(component);
        }

        void ComponentStorage::remove(const Entity& entity) noexcept {
            if (entityToIndex.find(entity.getID()) == entityToIndex.end()) {
                return;
            }
            const uint64 index = entityToIndex[entity.getID()];
            entityToIndex.erase(entity.getID());
            if (index != components.size() - 1) {
                components[index] = components.back();
            }
            components.pop_back();
        }

        Component& ComponentStorage::get(const Entity& entity) noexcept { return components[entityToIndex[entity.getID()]]; }

        const Component& ComponentStorage::get(const Entity& entity) const noexcept { return components[entityToIndex.at(entity.getID())]; }
    }  // namespace core::ecs
}  // namespace cobalt