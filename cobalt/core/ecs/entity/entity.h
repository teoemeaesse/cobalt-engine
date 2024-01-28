// Created by tomas on
// 18-01-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ComponentRegistry;

        /** @brief: ECS entity class. Just a handle to a component mask.
         */
        class Entity {
            friend class EntityRegistry;

            public:
            using ID = uint64;       // Entity ID - unique between all entities.
            using Version = uint64;  // Entity version - incremented every time an entity with this ID is destroyed.

            /** @brief: Default constructor. Users should never call this.
             * @param id: Entity ID. Should be unique.
             * @param version: Entity version. Should be unique.
             * @param entityRegistry: Entity registry.
             * @param componentRegistry: Component registry.
             * @return: Entity instance.
             */
            Entity(const ID id, const Version version, EntityRegistry& entityRegistry, ComponentRegistry& componentRegistry) noexcept;
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
            void addComponent() noexcept;

            /** @brief: Remove a component from the entity.
             * @tparam T: Component type.
             */
            template <typename T>
            void removeComponent() noexcept;

            /** @brief: Check if the entity has a component.
             * @tparam T: Component type.
             * @return: True if the entity has the component, false otherwise.
             */
            template <typename T>
            const bool hasComponent() const noexcept;

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
            const ID getID() const;

            /** @brief: Get the entity's version.
             * @return: Entity version.
             */
            const Version getVersion() const;

            private:
            const ID id;
            Version version;
            EntityRegistry& entityRegistry;
            ComponentRegistry& componentRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt