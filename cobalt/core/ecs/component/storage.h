// Created by tomas on
// 21-01-2024

#pragma once

#include "core/ecs/component/component.h"
#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        /** @brief: Interface for component storage.
         * TODO: This uses virtual functions, which might not be ideal for this performance-critical code.
         */
        class ComponentStorageInterface {
            public:
            virtual ~ComponentStorageInterface() = default;

            /** @brief: Adds a component to the storage.
             * @param entity: The entity to which the component belongs.
             * @param component: Component to add.
             */
            virtual void add(const Entity& entity, const Component& component) noexcept = 0;

            /** @brief: Removes a component from the storage.
             * @param entity: The entity to which the component belongs.
             */
            virtual void remove(const Entity& entity) noexcept = 0;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A reference to the component.
             */
            virtual Component& get(const Entity& entity) noexcept = 0;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A const reference to the component.
             */
            virtual const Component& get(const Entity& entity) const noexcept = 0;
        };

        /** @brief: Packed array of components. Maps entity IDs to components.
         * @tparam T: Component type.
         */
        template <typename T>
        class ComponentStorage : public ComponentStorageInterface {
            friend class ComponentStorageInterface;

            private:
            ComponentStorage();
            ~ComponentStorage() = default;

            /** @brief: Adds a component to the storage.
             * @param entity: The entity to which the component belongs.
             * @param component: Component to add.
             */
            void add(const Entity& entity, const T& component) noexcept override;

            /** @brief: Removes a component from the storage.
             * @param entity: The entity to which the component belongs.
             */
            void remove(const Entity& entity) noexcept override;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A reference to the component.
             */
            T& get(const Entity& entity) noexcept override;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A const reference to the component.
             */
            const T& get(const Entity& entity) const noexcept override;

            private:
            UMap<Entity::ID, uint64> entityToIndex;  // Maps entity IDs to component indices.
            Vec<T> components;                       // Packed array of components.
        };
    }  // namespace core::ecs
}  // namespace cobalt