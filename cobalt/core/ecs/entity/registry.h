// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/entity/entity.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry;

        /** @brief: Entity registry. Stores and manages all entities.
         */
        class EntityRegistry {
            friend class Entity;

            public:
            /** @brief: Default constructor.
             * @return: EntityRegistry instance.
             */
            EntityRegistry() noexcept = default;
            /** @brief: Default destructor.
             */
            ~EntityRegistry() = default;

            /** @brief: Create a new entity.
             * @param ComponentRegistry: Component registry for this entity's components.
             * @return: Entity ID.
             */
            Entity& add(ComponentRegistry& componentRegistry) noexcept;
            /** @brief: Destroy an entity.
             * @param id: Entity ID.
             */
            void remove(const Entity& entity) noexcept;

            /** @brief: The number of living entities in the registry.
             * @return: Number of living entities.
             */
            const uint64 getCount() const noexcept;

            private:
            UMap<Entity::ID, Entity> entities;  // All living entities.
            Queue<Entity::ID> freeIDs;          // Recently-freed IDs.

            /** @brief: Check if an entity is alive.
             * @param id: Entity ID.
             * @return: True if the entity is alive, false otherwise.
             */
            const bool isAlive(const Entity& entity) const noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt