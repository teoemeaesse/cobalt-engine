// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry;

        /** @brief: Entity registry. Stores and manages all entities.
         */
        class EntityRegistry {
            friend class Entity;

            public:
            /** @brief: Default constructor.
             * @param componentRegistry: ComponentRegistry instance.
             * @return: EntityRegistry instance.
             */
            EntityRegistry(ComponentRegistry& componentRegistry) noexcept;
            /** @brief: Default destructor.
             */
            ~EntityRegistry() = default;

            /** @brief: Create a new entity.
             * @return: Entity ID.
             */
            Entity& add() noexcept;
            /** @brief: Destroy an entity.
             * @param id: Entity ID.
             */
            void remove(Entity& entity) noexcept;

            /** @brief: The number of living entities in the registry.
             * @return: Number of living entities.
             */
            const uint64 getCount() const noexcept;

            private:
            UMap<Entity::ID, Entity> entities;     // All living entities.
            Queue<Entity::ID> freeIDs;             // Recently-freed IDs.
            ComponentRegistry& componentRegistry;  // Component registry.

            /** @brief: Check if an entity is alive.
             * @param id: Entity ID.
             * @return: True if the entity is alive, false otherwise.
             */
            const bool isAlive(const Entity& entity) const noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt