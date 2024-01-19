// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/component.h"

#define CB_MAX_COMPONENTS 1024

namespace cobalt {
    namespace core::ecs {
        /** @brief: ECS entity class. Just a handle to a component mask.
         */
        class Entity {
            public:
            using ID = uint64;

            /** @brief: Default constructor.
             * @param id: Entity ID. Should be unique.
             * @return: Entity instance.
             */
            Entity(const ID id);
            /** @brief: Default destructor.
             */
            ~Entity() = default;

            /** @brief: Add a component to the entity.
             * @param id: Component ID.
             */
            void addComponent(const Component::ID id);
            /** @brief: Remove a component from the entity.
             * @param id: Component ID.
             */
            void removeComponent(const Component::ID id);
            /** @brief: Check if the entity has a component.
             * @param id: Component ID.
             * @return: True if the entity has the component, false otherwise.
             */
            const bool hasComponent(const Component::ID id) const;

            /** @brief: Get the entity's ID.
             * @return: Entity ID.
             */
            const ID getID() const;

            private:
            const ID id;
            Mask<CB_MAX_COMPONENTS> mask;
        };
    }  // namespace core::ecs
}  // namespace cobalt