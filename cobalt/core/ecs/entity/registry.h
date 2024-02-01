// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry;

        /**
         * @brief: Entity registry. Stores and manages all entities.
         */
        class EntityRegistry {
            friend class Entity;

            public:
            /**
             * @brief: Default constructor.
             * @return: EntityRegistry instance.
             */
            EntityRegistry() noexcept = default;
            /**
             * @brief: Default destructor.
             */
            ~EntityRegistry() = default;
            /**
             * @brief: Copy constructor.
             * @param EntityRegistry: EntityRegistry to copy.
             * @return: EntityRegistry instance.
             */
            EntityRegistry(const EntityRegistry&) noexcept = delete;
            /**
             * @brief: Move constructor.
             * @param EntityRegistry: EntityRegistry to move.
             * @return: EntityRegistry instance.
             */
            EntityRegistry(EntityRegistry&&) noexcept = delete;
            /**
             * @brief: Copy assignment operator.
             * @param EntityRegistry: EntityRegistry to copy.
             * @return: EntityRegistry instance.
             */
            EntityRegistry& operator=(const EntityRegistry&) noexcept = delete;
            /**
             * @brief: Move assignment operator.
             * @param EntityRegistry: EntityRegistry to move.
             * @return: EntityRegistry instance.
             */
            EntityRegistry& operator=(EntityRegistry&&) noexcept = delete;

            /**
             * @brief: Create a new entity.
             * @param ComponentRegistry: Component registry for this entity's components.
             * @return: The new entity.
             */
            Entity& add(ComponentRegistry& componentRegistry) noexcept;
            /**
             * @brief: Destroy an entity.
             * @param entity: Entity to destroy.
             * @return: void
             */
            void remove(const Entity& entity) noexcept;
            /**
             * @brief: Destroy an entity.
             * @param entityID: ID of the entity to destroy.
             * @return: void
             */
            void remove(const EntityProperties::ID& entityID) noexcept;

            /**
             * @brief: The number entities in the registry.
             * @return: Number of entities.
             */
            const uint64 getSize() const noexcept;

            /**
             * @brief: Get a subset of entities' components.
             * @tparam Components...: Components to select for.
             * @return: A vector of tuples of references to components.
             */
            template <typename... Components>
            const Vec<Tuple<Components...>> get() const noexcept {
                static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");
                Vec<Tuple<Components...>> components;
                for (auto& entity : entities) {
                    if (entity.second.has<Components...>()) {
                        components.push_back(entity.second.get<Components...>());
                    }
                }
                return components;
            }

            private:
            UMap<EntityProperties::ID, Entity> entities;  // All living entities.
            Vec<uint64> versions;                         // Entity versions.
            Queue<EntityProperties::ID> freeIDs;          // Recently-freed IDs.

            /**
             * @brief: Check if an entity is alive.
             * @param id: Entity ID.
             * @return: True if the entity is alive, false otherwise.
             */
            const bool isAlive(const Entity& entity) const noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt