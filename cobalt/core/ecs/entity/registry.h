/**
 * @file registry.h
 * @brief Storage for every entity in the ECS.
 * @author Tomás Marques
 * @date 19-01-2024
 */

#pragma once

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry;

        /**
         * @brief Stores all entities and exposes an interface to interact with them.
         */
        class EntityRegistry {
            friend class Entity;

            public:
            /**
             * @brief Default constructor.
             * @param componentRegistry The component registry for this instance's entities.
             */
            EntityRegistry(ComponentRegistry& componentRegistry) noexcept;
            /**
             * @brief Default destructor.
             */
            ~EntityRegistry() noexcept = default;
            /**
             * @brief Copy constructor (deleted)
             * @param other The other EntityRegistry.
             */
            EntityRegistry(const EntityRegistry& other) noexcept = delete;
            /**
             * @brief Move constructor (deleted).
             * @param other The other EntityRegistry.
             */
            EntityRegistry(EntityRegistry&& other) noexcept = delete;
            /**
             * @brief Copy assignment operator (deleted).
             * @param other The other EntityRegistry.
             * @return Reference to this.
             */
            EntityRegistry& operator=(const EntityRegistry& other) noexcept = delete;
            /**
             * @brief Move assignment operator (deleted).
             * @param other The other EntityRegistry.
             * @return Reference to this.
             */
            EntityRegistry& operator=(EntityRegistry&& other) noexcept = delete;

            /**
             * @brief Create a new entity.
             * @return The new entity.
             */
            Entity& add() noexcept;
            /**
             * @brief Destroy an entity.
             * @param entity Entity to destroy.
             */
            void remove(const Entity& entity) noexcept;
            /**
             * @brief Destroy an entity.
             * @param entityID The ID of the entity to destroy.
             */
            void remove(const EntityProperties::ID& entityID) noexcept;

            /**
             * @brief The number entities in the registry.
             * @return The number of entities.
             */
            const uint64 getSize() const noexcept;

            /**
             * @brief Get a subset of all entities' components.
             * @tparam ComponentRefs... The components to select.
             * @return A vector of tuples of references to components.
             */
            template <typename... ComponentRefs>
            const Vec<Tuple<ComponentRefs...>> getMany() const noexcept {
                static_assert((std::is_reference<ComponentRefs>::value && ...), "All component types must be reference types.");
                Vec<Tuple<ComponentRefs...>> components;
                for (auto& entity : entities) {
                    if (entity.second.has<RemoveConstRef<ComponentRefs>...>()) {
                        components.push_back(entity.second.getMany<ComponentRefs...>());
                    }
                }
                return components;
            }
            /**
             * @brief Get a subset of all entities' components.
             * @tparam ComponentTypes... The components to select for.
             * @return A vector of tuples of references to components.
             */
            template <typename... ComponentTypes>
            const Vec<Tuple<const Entity&, ComponentTypes...>> getWithEntity() const noexcept {
                static_assert((std::is_reference<ComponentTypes>::value && ...), "All component types must be reference types.");
                Vec<Tuple<const Entity&, ComponentTypes...>> components;
                for (auto& entity : entities) {
                    if (entity.second.has<RemoveConstRef<ComponentTypes>...>()) {
                        components.push_back(std::tuple_cat(std::make_tuple(std::cref(entity.second)), entity.second.getMany<ComponentTypes...>()));
                    }
                }
                return components;
            }

            private:
            UMap<EntityProperties::ID, Entity> entities;  ///< All living entities.
            Vec<uint64> versions;                         ///< Entity versions.
            Queue<EntityProperties::ID> freeIDs;          ///< Recently-freed IDs.
            ComponentRegistry& componentRegistry;         ///< Component registry for this instance's entities.

            /**
             * @brief Check if an entity is alive.
             * @param entity The entity to check.
             * @return True if the entity is alive, false otherwise.
             */
            const bool isAlive(const Entity& entity) const noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt