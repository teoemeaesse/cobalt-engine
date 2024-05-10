/**
 * @file entity.h
 * @brief Defines the Entity class, which is essentially a handle to a component mask in the ECS.
 * @author Tomás Marques
 * @date 18-01-2024
 */

#pragma once

#include "core/ecs/component/registry.h"

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;

        /**
         * @brief ECS entity class. Just a handle to a component mask.
         */
        class Entity {
            friend class EntityRegistry;

            public:
            /**
             * @brief Default constructor. Users should never call this.
             * @param id The entity's ID. Should be unique.
             * @param version The entity's version.
             * @param entityRegistry The entity's registry.
             * @param componentRegistry The component registry for this entity.
             */
            Entity(const EntityProperties::ID id, const EntityProperties::Version version, EntityRegistry& entityRegistry,
                   ComponentRegistry& componentRegistry) noexcept;
            /**
             * @brief Default destructor.
             */
            ~Entity() = default;
            /**
             * @brief Copy constructor.
             * @param other The entity to copy.
             */
            Entity(const Entity& other) noexcept = delete;
            /**
             * @brief Move constructor.
             * @param other The entity to move.
             */
            Entity(Entity&& other) noexcept;

            /**
             * @brief Copy assignment operator.
             * @param other The entity to copy.
             * @return Reference to this.
             */
            Entity& operator=(const Entity& other) noexcept = delete;
            /**
             * @brief Move assignment operator.
             * @param other The entity to move.
             * @return Reference to this.
             */
            Entity& operator=(Entity&& other) noexcept = delete;

            /**
             * @brief Add a component to the entity.
             * @tparam ComponentType The component type.
             */
            template <typename ComponentType>
            void add() noexcept {
                componentRegistry.add<ComponentType>(id);
            }

            /**
             * @brief Add a component to the entity.
             * @tparam ComponentType The component type.
             * @tparam Args The component's constructor argument types.
             * @param args The component's constructor arguments.
             */
            template <typename ComponentType, typename... Args>
            void add(Args&&... args) noexcept {
                componentRegistry.add<ComponentType>(id, std::forward<Args>(args)...);
            }

            /**
             * @brief Remove a set of components from the entity.
             * @tparam ComponentTypes... The component types.
             */
            template <typename... ComponentTypes>
            void remove() noexcept {
                componentRegistry.remove<ComponentTypes...>(id);
            }

            /**
             * @brief Check if the entity has a set of components.
             * @tparam ComponentTypes... The component types.
             * @return True if the entity has the components, false otherwise.
             */
            template <typename... ComponentTypes>
            const bool has() const noexcept {
                return componentRegistry.has<ComponentTypes...>(id);
            }

            /**
             * @brief Get a set of components from the entity.
             * @tparam ComponentRefs... The component types.
             * @return The references to the components.
             */
            template <typename... ComponentRefs>
            Tuple<ComponentRefs...> getMany() const {
                static_assert((std::is_reference<ComponentRefs>::value && ...), "All component types must be reference types.");
                return componentRegistry.getMany<ComponentRefs...>(id);
            }
            /**
             * @brief Get a component from the entity.
             * @tparam ComponentRef The component reference.
             * @return A mutable reference to the component.
             */
            template <typename ComponentRef>
            ComponentRef get() {
                static_assert(std::is_reference<ComponentRef>::value,
                              "cobalt::core::ecs::ComponentRegistry threw: Component type must be a reference type.");
                return componentRegistry.get<ComponentRef>(id);
            }
            /**
             * @brief Get a component from the entity.
             * @tparam ComponentRef The component type reference.
             * @return A const reference to the component.
             */
            template <typename ComponentRef>
            ComponentRef get() const {
                static_assert(std::is_reference<ComponentRef>::value, "Component type must be a reference type.");
                return componentRegistry.get<ComponentRef>(id);
            }

            /**
             * @brief Kill the entity. This will remove all of its components and invalidate it.
             */
            void kill() const noexcept;

            /**
             * @brief Check if the entity is alive.
             * @return True if the entity is alive, false otherwise.
             */
            const bool isAlive() const noexcept;

            /**
             * @brief Equality operator.
             * @param other The other entity.
             * @return True if the entities are equal, false otherwise.
             */
            bool operator==(const Entity& other) const;

            /**
             * @brief Get this entity's ID.
             * @return This entity's ID.
             */
            const EntityProperties::ID getID() const;

            /**
             * @brief Get this entity's version.
             * @return This entity's version.
             */
            const EntityProperties::Version getVersion() const;

            private:
            const EntityProperties::ID id;         ///< This entity's ID.
            EntityProperties::Version version;     ///< This entity's version.
            EntityRegistry& entityRegistry;        ///< This registry this entity belongs to.
            ComponentRegistry& componentRegistry;  ///< The component registry for this entity.
        };
    }  // namespace core::ecs
}  // namespace cobalt