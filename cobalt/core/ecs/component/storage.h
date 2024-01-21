// Created by tomas on
// 21-01-2024

#pragma once

#include "core/ecs/component/component.h"
#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        /** @brief: Packed array of components.
         * Maps entity IDs to components.
         */
        class ComponentStorage {
            public:
            ComponentStorage() = default;
            ~ComponentStorage() = default;

            /** @brief: Adds a component to the storage.
             * @param entityID: ID of the entity to which the component belongs.
             * @param component: Component to add.
             */
            void add(const Entity::ID entityID, const Component& component) noexcept;

            /** @brief: Removes a component from the storage.
             * @param entityID: ID of the entity to which the component belongs.
             */
            void remove(const Entity::ID entityID) noexcept;

            /** @brief: Gets a component from the storage.
             * @param entityID: ID of the entity to which the component belongs.
             * @return: A reference to the component.
             */
            Component& get(const Entity::ID entityID) noexcept;

            /** @brief: Gets a component from the storage.
             * @param entityID: ID of the entity to which the component belongs.
             * @return: A const reference to the component.
             */
            const Component& get(const Entity::ID entityID) const noexcept;

            private:
            UMap<Entity::ID, uint64> entityToIndex;  // Maps entity IDs to component indices.
            Vec<Component> components;               // Packed array of components.
        };
    }  // namespace core::ecs
}  // namespace cobalt