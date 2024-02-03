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
            /**
             * @brief: Default constructor.
             * @return: ComponentRegistry instance.
             */
            ComponentRegistry() noexcept = default;
            /**
             * @brief: Default destructor.
             */
            ~ComponentRegistry() = default;
            /**
             * @brief: Copy constructor.
             * @param other: ComponentRegistry instance to copy.
             */
            ComponentRegistry(const ComponentRegistry&) noexcept = delete;
            /**
             * @brief: Move constructor.
             * @param other: ComponentRegistry instance to move.
             */
            ComponentRegistry(ComponentRegistry&&) noexcept = delete;
            /**
             * @brief: Copy assignment operator.
             * @param other: ComponentRegistry instance to copy.
             * @return: Reference to this.
             */
            ComponentRegistry& operator=(const ComponentRegistry&) noexcept = delete;
            /**
             * @brief: Move assignment operator.
             * @param other: ComponentRegistry instance to move.
             * @return: Reference to this.
             */
            ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;

            /**
             * @brief: Register a component type.
             * @tparam ComponentType: Component type.
             * @return: void
             */
            template <typename ComponentType>
            void registerComponent() {
                Component::template validate<ComponentType>();
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    if (typeIndices.size() >= CB_ECS_MAX_COMPONENTS) {
                        throw ComponentOverflowException<ComponentType>(CB_ECS_MAX_COMPONENTS);
                    }
                    store[type] = Move(createScope<ComponentStorage<ComponentType>>());
                    const uint64 index = typeIndices.size();
                    typeIndices[type] = index;
                }
            }

            /**
             * @brief: Add a component to an entity.
             * @tparam ComponentType: Component type.
             * @param entityID: The entity ID.
             * @return: void
             */
            template <typename ComponentType>
            void add(const EntityProperties::ID& entityID) noexcept {
                Component::template validate<ComponentType>();
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered", Component::template getTypeName<ComponentType>());
                    return;
                }
                store[type]->add(entityID, ComponentType());
                signatures[entityID].set(typeIndices[type]);
            }
            /**
             * @brief: Add a component to an entity.
             * @tparam ComponentType: Component type.
             * @param entityID: The entity ID.
             * @param args: Component's constructor arguments.
             * @return: void
             */
            template <typename ComponentType, typename... Args>
            void add(const EntityProperties::ID& entityID, Args&&... args) noexcept {
                Component::template validate<ComponentType>();
                static_assert(std::is_constructible<ComponentType, Args...>::value, "T must be constructible with Args.");
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered", Component::template getTypeName<ComponentType>());
                    return;
                }
                store[type]->add(entityID, ComponentType(std::forward<Args>(args)...));
                signatures[entityID].set(typeIndices[type]);
            }

            /**
             * @brief: Remove a set of components from an entity.
             * @tparam Components...: Component types.
             * @param entityID: The entity ID.
             * @return: void
             */
            template <typename... Components>
            void remove(const EntityProperties::ID& entityID) noexcept {
                Component::template validate<Components...>();
                try {
                    (store.at(Component::getType<Components>())->remove(entityID), ...);
                } catch (const std::out_of_range& e) {
                    CB_CORE_WARN("Component not registered", e.what());
                    return;
                }
                (signatures[entityID].reset(typeIndices.at(Component::template getType<Components>())), ...);
            }
            /**
             * @brief: Remove all components from an entity.
             * @param entityID: The entity ID.
             * @return: void
             */
            void removeAll(const EntityProperties::ID& entityID) noexcept;

            template <typename ComponentType>
            ComponentType& getSingleComponent(const EntityProperties::ID& entityID) {
                try {
                    return static_cast<ComponentType&>(store.at(Component::template getType<RemoveConstRef<ComponentType>>())->get(entityID));
                } catch (const std::out_of_range& e) {
                    throw ComponentNotFoundException<RemoveConstRef<ComponentType>>(entityID);
                }
            }
            /**
             * @brief: Get a component from an entity.
             * @tparam ComponentType: Component type.
             * @param entityID: The entity ID.
             * @return: Component reference.
             */
            template <typename ComponentType>
            const ComponentType& getSingleComponent(const EntityProperties::ID& entityID) const {
                try {
                    return static_cast<const ComponentType&>(store.at(Component::template getType<RemoveConstRef<ComponentType>>())->get(entityID));
                } catch (const std::out_of_range& e) {
                    throw ComponentNotFoundException<RemoveConstRef<ComponentType>>(entityID);
                }
            }

            /**
             * @brief: Get a set of components from an entity.
             * @tparam Components...: Component types.
             * @param entityID: The entity ID.
             * @return: Component reference.
             */
            template <typename... Components>
            Tuple<Components...> get(const EntityProperties::ID& entityID) const {
                static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");
                Component::template validate<RemoveConstRef<Components>...>();
                return (std::make_tuple(std::ref(getSingleComponent<Components>(entityID))...));
            }

            /**
             * @brief: Check if an entity has a set of components.
             * @tparam Components...: Component types.
             * @param entityID: The entity ID.
             * @return: True if the entity has the components, false otherwise.
             */
            template <typename... Components>
            const bool has(const EntityProperties::ID& entityID) const {
                Component::template validate<RemoveConstRef<Components>...>();
                return signatures.find(entityID) != signatures.end() &&
                       (signatures.at(entityID).test(typeIndices.at(Component::template getType<Components>())) && ...);
            }

            private:
            UMap<ComponentProperties::Type, Scope<ComponentStorageInterface>> store;  // Component storage.
            UMap<EntityProperties::ID, Mask<CB_ECS_MAX_COMPONENTS>> signatures;       // Entity signatures.
            UMap<ComponentProperties::Type, uint64> typeIndices;                      // Map component types to indices into the signature mask.
        };
    }  // namespace core::ecs
}  // namespace cobalt