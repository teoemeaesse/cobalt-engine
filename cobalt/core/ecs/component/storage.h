// Created by tomas on
// 21-01-2024

#pragma once

#include "core/ecs/component/component.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Interface for component storage.
         * TODO: This uses virtual functions, which might not be ideal for this performance-critical code.
         */
        class ComponentStorageInterface {
            public:
            virtual ~ComponentStorageInterface() = default;

            /**
             * @brief: Adds a component to the storage.
             * @param entityID: The ID of its entity.
             * @param component: Component to add.
             * @return: void
             */
            virtual void add(const EntityProperties::ID& entityID, const Component& component) noexcept = 0;

            /**
             * @brief: Removes a component from the storage.
             * @param entityID: The ID of its entity.
             * @return: void
             */
            virtual void remove(const EntityProperties::ID& entityID) noexcept = 0;

            /**
             * @brief: Gets a component from the storage.
             * @param entityID: The ID of its entity.
             * @return: A reference to the component.
             */
            virtual Component& get(const EntityProperties::ID& entityID) = 0;

            /**
             * @brief: Gets a component from the storage.
             * @param entityID: The ID of its entity.
             * @return: A const reference to the component.
             */
            virtual const Component& get(const EntityProperties::ID& entityID) const = 0;
        };

        /**
         * @brief: Packed array of components. Maps entity IDs to components.
         * @tparam T: Component type.
         */
        template <typename T>
        class ComponentStorage : public ComponentStorageInterface {
            friend class ComponentStorageInterface;

            static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
            static_assert(std::is_default_constructible<T>::value, "T must be default constructible.");
            static_assert(std::is_copy_constructible<T>::value, "T must be copy constructible.");

            public:
            ComponentStorage() = default;
            ~ComponentStorage() = default;

            private:
            /**
             * @brief: Adds a component to the storage.
             * @param entity: The entity to which the component belongs.
             * @param component: Component to add.
             * @return: void
             */
            void add(const EntityProperties::ID& entityID, const Component& component) noexcept override {
                if (entityToIndex.find(entityID) != entityToIndex.end()) {
                    return;
                }
                entityToIndex[entityID] = components.size();
                components.push_back(dynamic_cast<const T&>(component));
            }

            /**
             * @brief: Removes a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: void
             */
            void remove(const EntityProperties::ID& entityID) noexcept override {
                if (entityToIndex.find(entityID) == entityToIndex.end()) {
                    return;
                }
                const uint64 index = entityToIndex[entityID];
                entityToIndex.erase(entityID);
                if (index != components.size() - 1) {
                    components[index] = components.back();
                }
                components.pop_back();
            }

            /**
             * @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A reference to the component.
             */
            Component& get(const EntityProperties::ID& entityID) override { return components[entityToIndex.at(entityID)]; }

            /**
             * @brief: Gets a component from the storage.
             * @param entity: The entity to which the component belongs.
             * @return: A const reference to the component.
             */
            const Component& get(const EntityProperties::ID& entityID) const override { return components[entityToIndex.at(entityID)]; }

            private:
            UMap<EntityProperties::ID, uint64> entityToIndex;  // Maps entity IDs to component indices.
            Vec<T> components;                                 // Packed array of components.
        };
    }  // namespace core::ecs
}  // namespace cobalt