// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry {
            public:
            /** @brief: Default constructor.
             * @return: EntityRegistry instance.
             */
            EntityRegistry() = default;
            /** @brief: Default destructor.
             */
            ~EntityRegistry() = default;

            /** @brief: Create a new entity.
             * @return: Entity ID.
             */
            const Entity::ID createEntity() noexcept;
            /** @brief: Destroy an entity.
             * @param id: Entity ID.
             */
            void destroyEntity(const Entity::ID id) noexcept;
            /** @brief: Check if an entity is alive.
             * @param id: Entity ID.
             * @return: True if the entity is alive, false otherwise.
             */
            const bool isAlive(const Entity::ID id) const noexcept;

            /** @brief: The number of living entities in the registry.
             * @return: Number of living entities.
             */
            const uint64 getEntityCount() const noexcept;

            private:
            UMap<Entity::ID, Entity> entities;  // All living entities.
            Queue<Entity::ID> freeIDs;          // Recently-freed IDs.
        };
    }  // namespace core::ecs
}  // namespace cobalt