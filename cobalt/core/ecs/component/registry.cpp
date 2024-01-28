// Created by tomas on
// 24-01-2024

#include "core/ecs/component/registry.h"

#include "core/exceptions/ecs_exception.h"

namespace cobalt {
    namespace core::ecs {
        template <typename T>
        void ComponentRegistry::registerComponent() {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                if (typeIndices.size() >= CB_ECS_MAX_COMPONENTS) {
                    throw ComponentOverflowException<T>(CB_ECS_MAX_COMPONENTS);
                }
                store[type] = std::move(createScope<ComponentStorage<T>>());
                const uint64 index = typeIndices.size();
                typeIndices[type] = index;
            }
        }

        template <typename T>
        void ComponentRegistry::add(const Entity& entity) noexcept {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                CB_CORE_WARN("Component \"{0}\" not registered.", Component::getTypeName<T>());
                return;
            }
            store[type]->add(entity, T());
            signatures[entity.getID()].set(typeIndices[type]);
        }

        template <typename T, typename... Args>
        void ComponentRegistry::add(const Entity& entity, Args&&... args) noexcept {
            Component::validateComponent<T>();
            static_assert(std::is_constructible<T, Args...>::value, "T must be constructible with Args.");
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                CB_CORE_WARN("Component \"{0}\" not registered.", Component::getTypeName<T>());
                return;
            }
            store[type]->add(entity, T(std::forward<Args>(args)...));
            signatures[entity.getID()].set(typeIndices[type]);
        }

        template <typename T>
        void ComponentRegistry::remove(const Entity& entity) noexcept {
            Component::validateComponent<T>();
            const Component::Type type = Component::getType<T>();
            if (store.find(type) == store.end()) {
                return;
            }
            store[type]->remove(entity);
            signatures[entity.getID()].reset(typeIndices[type]);
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