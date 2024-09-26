/**
 * @file registry.h
 * @brief Storage for every type of components in the ECS.
 * @author Tomás Marques
 * @date 19-01-2024
 */

#pragma once

#include "core/ecs/component/storage.h"
#include "core/ecs/exception.h"
#include "core/utils/log.h"

#define CB_ECS_MAX_COMPONENTS 64

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Registry class to store all components in a central location.
         */
        class ComponentRegistry {
            public:
            /**
             * @brief Default constructor.
             */
            ComponentRegistry() noexcept = default;
            /**
             * @brief Default destructor.
             */
            ~ComponentRegistry() = default;
            /**
             * @brief Copy constructor (deleted).
             * @param other The ComponentRegistry to copy.
             */
            ComponentRegistry(const ComponentRegistry&) noexcept = delete;
            /**
             * @brief Move constructor (deleted).
             * @param other The ComponentRegistry to move.
             */
            ComponentRegistry(ComponentRegistry&&) noexcept = delete;
            /**
             * @brief Copy assignment operator (deleted).
             * @param other The ComponentRegistry to copy.
             */
            ComponentRegistry& operator=(const ComponentRegistry&) noexcept = delete;
            /**
             * @brief Move assignment operator (deleted).
             * @param other The ComponentRegistry to move.
             */
            ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;

            /**
             * @brief Register a component type.
             * @tparam ComponentType The component type.
             */
            template <typename ComponentType>
            void registerComponent() {
                Component::template validate<ComponentType>();
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    if (typeIndices.size() >= CB_ECS_MAX_COMPONENTS) {
                        throw ComponentOverflowException<ComponentType, ComponentRegistry>(CB_ECS_MAX_COMPONENTS);
                    }
                    store[type] = std::move(std::make_unique<ComponentStorage<ComponentType>>());
                    const u_int64_t index = typeIndices.size();
                    typeIndices[type] = index;
                }
            }

            /**
             * @brief Add a component to an entity.
             * @tparam ComponentType The component type.
             * @param entityID The entity to add the component to.
             */
            template <typename ComponentType>
            void add(const EntityProperties::ID& entityID) noexcept {
                Component::template validate<ComponentType>();
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered", Component::template getTypeName<ComponentType>());
                    return;
                }
                store[type]->add(entityID, ComponentType());
                signatures[entityID].set(typeIndices[type]);
            }
            /**
             * @brief Add a component to an entity.
             * @tparam ComponentType The component type.
             * @param entityID The entity to add the component to.
             * @param args The component's constructor arguments.
             */
            template <typename ComponentType, typename... Args>
            void add(const EntityProperties::ID& entityID, Args&&... args) noexcept {
                Component::template validate<ComponentType>();
                static_assert(std::is_constructible<ComponentType, Args...>::value, "T must be constructible with Args.");
                const ComponentProperties::Type type = Component::template getType<ComponentType>();
                if (store.find(type) == store.end()) {
                    CB_CORE_WARN("Component \"{0}\" not registered", Component::template getTypeName<ComponentType>());
                    return;
                }
                store[type]->add(entityID, ComponentType(std::forward<Args>(args)...));
                signatures[entityID].set(typeIndices[type]);
            }

            /**
             * @brief Remove a set of components from an entity.
             * @tparam ComponentTypes... The component types.
             * @param entityID The entity to remove the components from.
             */
            template <typename... ComponentTypes>
            void remove(const EntityProperties::ID& entityID) noexcept {
                Component::template validate<ComponentTypes...>();
                try {
                    (store.at(Component::getType<ComponentTypes>())->remove(entityID), ...);
                } catch (const std::out_of_range& e) {
                    CB_CORE_WARN("Component not registered", e.what());
                    return;
                }
                (signatures[entityID].reset(typeIndices.at(Component::template getType<ComponentTypes>())), ...);
            }
            /**
             * @brief Remove all the components from an entity.
             * @param entityID The entity to remove the components from.
             */
            void removeAll(const EntityProperties::ID& entityID) noexcept;

            /**
             * @brief Get a component from an entity.
             * @tparam ComponentRef The component type.
             * @param entityID The entity to get the component from.
             * @return Mutable reference to the component.
             */
            template <typename ComponentRef>
            ComponentRef get(const EntityProperties::ID& entityID) {
                try {
                    return dynamic_cast<ComponentRef>(
                        store.at(Component::template getType<std::remove_const_t<std::remove_reference_t<ComponentRef>>>())->get(entityID));
                } catch (const std::out_of_range& e) {
                    throw ComponentNotFoundException<std::remove_const_t<std::remove_reference_t<ComponentRef>>, ComponentRegistry>(entityID);
                }
            }
            /**
             * @brief Get a component from an entity.
             * @tparam ComponentRef The component type reference.
             * @param entityID The entity to get the component from.
             * @return Const reference to the component.
             */
            template <typename ComponentRef>
            ComponentRef get(const EntityProperties::ID& entityID) const {
                try {
                    return dynamic_cast<ComponentRef>(
                        store.at(Component::template getType<std::remove_const_t<std::remove_reference_t<ComponentRef>>>())->get(entityID));
                } catch (const std::out_of_range& e) {
                    throw ComponentNotFoundException<std::remove_const_t<std::remove_reference_t<ComponentRef>>, ComponentRegistry>(entityID);
                }
            }

            /**
             * @brief Get a set of components from an entity.
             * @tparam ComponentRefs... The component types references.
             * @param entityID The entity to get the components from.
             * @return References to the components.
             */
            template <typename... ComponentRefs>
            std::tuple<ComponentRefs...> getMany(const EntityProperties::ID& entityID) const {
                Component::template validate<std::remove_const_t<std::remove_reference_t<ComponentRefs>>...>();
                return (std::make_tuple(std::ref(get<ComponentRefs>(entityID))...));
            }

            /**
             * @brief Check if an entity has a set of components.
             * @tparam ComponentTypes... The component types references.
             * @param entityID The entity to check.
             * @return True if the entity has the components, false otherwise.
             */
            template <typename... ComponentTypes>
            const bool has(const EntityProperties::ID& entityID) const {
                Component::template validate<ComponentTypes...>();
                return signatures.find(entityID) != signatures.end() &&
                       (signatures.at(entityID).test(typeIndices.at(Component::template getType<ComponentTypes>())) && ...);
            }

            private:
            std::unordered_map<ComponentProperties::Type, std::unique_ptr<ComponentStorageInterface>>
                store;  ///< Component store. Maps component types to their storage.
            std::unordered_map<EntityProperties::ID, std::bitset<CB_ECS_MAX_COMPONENTS>>
                signatures;  ///< Entity signatures. Maps entity IDs to their component signatures.
            std::unordered_map<ComponentProperties::Type, u_int64_t> typeIndices;  ///< Maps component types to indices into their signature mask.
        };
    }  // namespace core::ecs
}  // namespace cobalt