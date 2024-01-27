// Created by tomas on
// 21-01-2024

#include "core/ecs/component/storage.h"

namespace cobalt {
    namespace core::ecs {
        template <typename T>
        ComponentStorage<T>::ComponentStorage() : ComponentStorageInterface() {
            Component::validateComponent<T>();
        }

        template <typename T>
        void ComponentStorage<T>::add(const Entity& entity, const T& component) noexcept {
            if (entityToIndex.find(entity.getID()) != entityToIndex.end()) {
                return;
            }
            entityToIndex[entity.getID()] = components.size();
            components.push_back(component);
        }

        template <typename T>
        void ComponentStorage<T>::remove(const Entity& entity) noexcept {
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

        template <typename T>
        T& ComponentStorage<T>::get(const Entity& entity) noexcept {
            return components[entityToIndex[entity.getID()]];
        }

        template <typename T>
        const T& ComponentStorage<T>::get(const Entity& entity) const noexcept {
            return components[entityToIndex.at(entity.getID())];
        }
    }  // namespace core::ecs
}  // namespace cobalt