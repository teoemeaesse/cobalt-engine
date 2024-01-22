// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/component/storage.h"
#include "core/exceptions/ecs_exception.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry {
            public:
            /** @brief: Default constructor.
             * @return: ComponentRegistry instance.
             */
            ComponentRegistry() = default;
            /** @brief: Default destructor.
             */
            ~ComponentRegistry() = default;

            /** @brief: Add a component to an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             */
            template <typename T>
            void add(const Entity& entity) noexcept {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    store[type] = ComponentStorage();
                }
                store[type].add(entity, T());
            }

            /** @brief: Remove a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             */
            template <typename T>
            void remove(const Entity& entity) noexcept {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    return;
                }
                store[type].remove(entity);
            }

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: Component reference.
             */
            template <typename T>
            T& get(const Entity& entity) {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entity.getID());
                }
                return store[type].get(entity);
            }

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: Component reference.
             */
            template <typename T>
            const T& get(const Entity& entity) const {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                const Component::Type type = typeid(T).hash_code();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entity.getID());
                }
                return store.at(type).get(entity);
            }

            /** @brief: Check if an entity has a component.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: True if the entity has the component, false otherwise.
             */
            template <typename T>
            const bool has(const Entity& entity) const {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                return store.find(typeid(T).hash_code()) != store.end();
            }

            private:
            UMap<Component::Type, ComponentStorage> store;  // Component storage.
        };
    }  // namespace core::ecs
}  // namespace cobalt