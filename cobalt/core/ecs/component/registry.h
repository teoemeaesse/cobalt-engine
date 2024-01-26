// Created by tomas on
// 19-01-2024

#pragma once

#include "core/ecs/component/storage.h"
#include "core/exceptions/ecs_exception.h"

namespace cobalt {
    namespace core::ecs {
        class ComponentRegistry {
            public:
            /** @brief: Default constructor.
             * @return: ComponentRegistry instance.
             */
            ComponentRegistry() = default;
            /** @brief: Default destructor.
             */
            ~ComponentRegistry() = default;

            /** @brief: Add a component to an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             */
            template <typename T>
            void add(const Entity& entity) noexcept;

            /** @brief: Add a component to an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @param args: Component's constructor arguments.
             */
            template <typename T, typename... Args>
            void add(const Entity& entity, Args&&... args) noexcept;

            /** @brief: Remove a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             */
            template <typename T>
            void remove(const Entity& entity) noexcept;

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: Component reference.
             */
            template <typename T>
            T& get(const Entity& entity);

            /** @brief: Get a component from an entity.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: Component reference.
             */
            template <typename T>
            const T& get(const Entity& entity) const;

            /** @brief: Check if an entity has a component.
             * @tparam T: Component type.
             * @param entity: The entity.
             * @return: True if the entity has the component, false otherwise.
             */
            template <typename T>
            const bool has(const Entity& entity) const;

            private:
            UMap<Component::Type, ComponentStorage> store;  // Component storage.
        };
    }  // namespace core::ecs
}  // namespace cobalt