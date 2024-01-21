// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/component/storage.h"
#include "core/exceptions/ecs_exception.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry {
            public:
            ComponentRegistry() = default;
            ~ComponentRegistry() = default;

            template <typename T>
            void add(const Entity::ID entityID) noexcept {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    store[type] = ComponentStorage();
                }
                store[type].add(entityID, T());
            }

            template <typename T>
            void remove(const Entity::ID entityID) noexcept {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    return;
                }
                store[type].remove(entityID);
            }

            template <typename T>
            T& get(const Entity::ID entityID) {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entityID);
                }
                return store[type].get(entityID);
            }

            template <typename T>
            const T& get(const Entity::ID entityID) const {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entityID);
                }
                return store[type].get(entityID);
            }

            private:
            UMap<Component::Type, ComponentStorage> store;
        };
    }  // namespace core::ecs
}  // namespace cobalt