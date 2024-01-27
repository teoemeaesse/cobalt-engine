// Created by tomas on
// 24-01-2024

#include "core/ecs/component/registry.h"

namespace cobalt {
    namespace core::ecs {
        template <typename T>
        void ComponentRegistry::add(const Entity& entity) noexcept {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                store[type] = std::move(createScope<ComponentStorage<T>>());
            }
            store[type]->add(entity, T());
        }

        template <typename T, typename... Args>
        void ComponentRegistry::add(const Entity& entity, Args&&... args) noexcept {
            Component::validateComponent<T>();
            static_assert(std::is_constructible<T, Args...>::value, "T must be constructible with Args.");
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                store[type] = std::move(createScope<ComponentStorage<T>>());
            }
            store[type]->add(entity, T(std::forward<Args>(args)...));
        }

        template <typename T>
        void ComponentRegistry::remove(const Entity& entity) noexcept {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                return;
            }
            store[type]->remove(entity);
        }

        template <typename T>
        T& ComponentRegistry::get(const Entity& entity) {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                throw ComponentNotFoundException<T>(entity.getID());
            }
            return store.at(type)->get(entity);
        }

        template <typename T>
        const T& ComponentRegistry::get(const Entity& entity) const {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                throw ComponentNotFoundException<T>(entity.getID());
            }
            return store.at(type)->get(entity);
        }

        template <typename T>
        const bool ComponentRegistry::has(const Entity& entity) const {
            Component::validateComponent<T>();
            return store.find(Component::getType<T>()) != store.end();
        }
    }  // namespace core::ecs
}  // namespace cobalt