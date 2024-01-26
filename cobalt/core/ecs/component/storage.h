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
             * @param entity: The entity to which the component belongs.
             * @param component: Component to add.
             */
            void add(const Entity& entity, const Component& component) noexcept;

            /** @brief: Removes a component from the storage.
             * @param entity: The entity to which the component belongs.
             */
            void remove(const Entity& entity) noexcept;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A reference to the component.
             */
            Component& get(const Entity& entity) noexcept;

            /** @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A const reference to the component.
             */
            const Component& get(const Entity& entity) const noexcept;

            /** @brief: Iterator for the component storage.
             */
            class Iterator {
                public:
                Iterator(Component* component) : component(component) {}

                Component& operator*() const { return *component; }
                Component* operator->() { return component; }
                Iterator& operator++() {
                    component++;
                    return *this;
                }
                Iterator operator++(int) {
                    Iterator temp = *this;
                    ++(*this);
                    return temp;
                }
                bool operator==(const Iterator& it) { return component == it.component; }
                bool operator!=(const Iterator& it) { return component != it.component; }

                private:
                Component* component;
            };

            Iterator begin() { return Iterator(&components[0]); }

            Iterator end() { return Iterator(&components[0] + components.size()); }

            private:
            UMap<Entity::ID, uint64> entityToIndex;  // Maps entity IDs to component indices.
            Vec<Component> components;               // Packed array of components.
        };
    }  // namespace core::ecs
}  // namespace cobalt