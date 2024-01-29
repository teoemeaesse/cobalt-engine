// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/component/storage.h"
#include "core/exceptions/ecs_exception.h"

#define CB_ECS_MAX_COMPONENTS 64

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry {
            public:
            /** @brief: Default constructor.
             * @return: ComponentRegistry instance.
             */
            ComponentRegistry() noexcept = default;
            /** @brief: Default destructor.
             */
            ~ComponentRegistry() = default;
            /** @brief: Copy constructor.
             * @param other: ComponentRegistry instance to copy.
             */
            ComponentRegistry(const ComponentRegistry&) noexcept = delete;
            /** @brief: Move constructor.
             * @param other: ComponentRegistry instance to move.
             */
            ComponentRegistry(ComponentRegistry&&) noexcept = delete;
            /** @brief: Copy assignment operator.
             * @param other: ComponentRegistry instance to copy.
             * @return: Reference to this.
             */
            ComponentRegistry& operator=(const ComponentRegistry&) noexcept = delete;
            /** @brief: Move assignment operator.
             * @param other: ComponentRegistry instance to move.
             * @return: Reference to this.
             */
            ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;

            /** @brief: Register a component type.
             * @tparam T: Component type.
             */
            template <typename T>
            void registerComponent() {
                Component::validateComponent<T>();
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    if (typeIndices.size() >= CB_ECS_MAX_COMPONENTS) {
                        throw ComponentOverflowException<T>(CB_ECS_MAX_COMPONENTS);
                    }
                    store[type] = std::move(createScope<ComponentStorage<T>>());
                    const uint64 index = typeIndices.size();
                    typeIndices[type] = index;
                }
            }

            /** @brief: Add a component to an entity.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             */
            template <typename T>
            void add(const EntityProperties::ID& entityID) noexcept {
                Component::validateComponent<T>();
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered.", Component::getTypeName<T>());
                    return;
                }
                store[type]->add(entityID, T());
                signatures[entityID].set(typeIndices[type]);
            }

            /** @brief: Add a component to an entity.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             * @param args: Component's constructor arguments.
             */
            template <typename T, typename... Args>
            void add(const EntityProperties::ID& entityID, Args&&... args) noexcept {
                Component::validateComponent<T>();
                static_assert(std::is_constructible<T, Args...>::value, "T must be constructible with Args.");
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered.", Component::getTypeName<T>());
                    return;
                }
                store[type]->add(entityID, T(std::forward<Args>(args)...));
                signatures[entityID].set(typeIndices[type]);
            }

            /** @brief: Remove a component from an entity.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             */
            template <typename T>
            void remove(const EntityProperties::ID& entityID) noexcept {
                Component::validateComponent<T>();
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    return;
                }
                store[type]->remove(entityID);
                signatures[entityID].reset(typeIndices[type]);
            }

            /** @brief: Remove all components from an entity.
             * @param entityID: The entity ID.
             */
            void removeAll(const EntityProperties::ID& entityID) noexcept;

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             * @return: Component reference.
             */
            template <typename T>
            T& get(const EntityProperties::ID& entityID) {
                Component::validateComponent<T>();
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entityID);
                }
                return store.at(type)->get(entityID);
            }

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             * @return: Component reference.
             */
            template <typename T>
            const T& get(const EntityProperties::ID& entityID) const {
                Component::validateComponent<T>();
                const ComponentProperties::Type type = Component::getType<T>();
                if (store.find(type) == store.end()) {
                    throw ComponentNotFoundException<T>(entityID);
                }
                return store.at(type)->get(entityID);
            }

            /** @brief: Check if an entity has a component.
             * @tparam T: Component type.
             * @param entityID: The entity ID.
             * @return: True if the entity has the component, false otherwise.
             */
            template <typename T>
            const bool has(const EntityProperties::ID& entityID) const {
                Component::validateComponent<T>();
                return signatures.find(entityID) != signatures.end() && signatures.at(entityID).test(typeIndices.at(Component::getType<T>()));
            }

            private:
            UMap<ComponentProperties::Type, Scope<ComponentStorageInterface>> store;  // Component storage.
            UMap<EntityProperties::ID, Mask<CB_ECS_MAX_COMPONENTS>> signatures;       // Entity signatures.
            UMap<ComponentProperties::Type, uint64> typeIndices;                      // Map component types to indices into the signature mask.
        };
    }  // namespace core::ecs
}  // namespace cobalt