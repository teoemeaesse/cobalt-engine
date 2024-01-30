// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/registry.h"

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;

        /** @brief: ECS entity class. Just a handle to a component mask.
         */
        class Entity {
            friend class EntityRegistry;

            public:
            /** @brief: Default constructor. Users should never call this.
             * @param id: Entity ID. Should be unique.
             * @param version: Entity version. Should be unique.
             * @param entityRegistry: Entity registry.
             * @param componentRegistry: Component registry.
             * @return: Entity instance.
             */
            Entity(const EntityProperties::ID id, const EntityProperties::Version version, EntityRegistry& entityRegistry,
                   ComponentRegistry& componentRegistry) noexcept;
            /** @brief: Copy constructor.
             * @return: Entity instance.
             */
            Entity(const Entity& other) noexcept = delete;
            /** @brief: Move constructor.
             * @return: Entity instance.
             */
            Entity(Entity&& other) noexcept;
            /** @brief: Copy assignment operator.
             * @return: Reference to this.
             */
            Entity& operator=(const Entity& other) noexcept = delete;
            /** @brief: Move assignment operator.
             * @return: Reference to this.
             */
            Entity& operator=(Entity&& other) noexcept = delete;
            /** @brief: Default destructor.
             */
            ~Entity() = default;

            /** @brief: Add a component to the entity.
             * @tparam T: Component type.
             */
            template <typename T>
            void add() noexcept {
                componentRegistry.add<T>(id);
            }

            /** @brief: Add a component to the entity.
             * @tparam T: Component type.
             * @tparam Args: Component constructor arguments.
             * @param args: Component constructor arguments.
             */
            template <typename T, typename... Args>
            void add(Args&&... args) noexcept {
                componentRegistry.add<T>(id, std::forward<Args>(args)...);
            }

            /** @brief: Remove a set of components from the entity.
             * @tparam Types...: Component types.
             */
            template <typename... Types>
            void remove() noexcept {
                componentRegistry.remove<Types...>(id);
            }

            /** @brief: Check if the entity has a set of components.
             * @tparam Types: Component types.
             * @param entityID: The entity ID.
             * @return: True if the entity has the components, false otherwise.
             */
            template <typename... Types>
            const bool has() const noexcept {
                return componentRegistry.has<Types...>(id);
            }

            /** @brief: Kill the entity. This will remove all its components and invalidate it.
             */
            void kill() noexcept;

            /** @brief: Check if the entity is alive: living entities have a positive ID and the latest version.
             * @return: True if the entity is alive, false otherwise.
             */
            const bool isAlive() const noexcept;

            /** @brief: Equality operator.
             * @param other: Other entity.
             * @return: True if the entities are equal, false otherwise.
             */
            bool operator==(const Entity& other) const;

            /** @brief: Get the entity's ID.
             * @return: Entity ID.
             */
            const EntityProperties::ID getID() const;

            /** @brief: Get the entity's version.
             * @return: Entity version.
             */
            const EntityProperties::Version getVersion() const;

            private:
            const EntityProperties::ID id;
            EntityProperties::Version version;
            EntityRegistry& entityRegistry;
            ComponentRegistry& componentRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt