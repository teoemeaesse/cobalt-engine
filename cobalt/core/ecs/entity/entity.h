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
            using ID = uint64;  // Entity ID - unique between all entities.

            /** @brief: Copy constructor.
             * @return: Entity instance.
             */
            Entity(const Entity& other) noexcept = default;
            /** @brief: Move constructor.
             * @return: Entity instance.
             */
            Entity(Entity&& other) noexcept = default;
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

            /** @brief: Equality operator.
             * @param other: Other entity.
             * @return: True if the entities are equal, false otherwise.
             */
            bool operator==(const Entity& other) const;

            /** @brief: Get the entity's ID.
             * @return: Entity ID.
             */
            const ID getID() const;

            private:
            const ID id;
            const EntityRegistry& entityRegistry;
            const ComponentRegistry& componentRegistry;

            /** @brief: Default constructor.
             * @param id: Entity ID. Should be unique.
             * @param entityRegistry: Entity registry.
             * @param componentRegistry: Component registry.
             * @return: Entity instance.
             */
            Entity(const ID id, EntityRegistry& entityRegistry, ComponentRegistry& componentRegistry) noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt