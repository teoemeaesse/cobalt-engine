// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/entity.h"

#include "core/ecs/component/registry.h"

namespace cobalt {
    namespace core::ecs {
        Entity::Entity(const ID id, EntityRegistry& entityRegistry, ComponentRegistry& componentRegistry) noexcept
            : id(id), entityRegistry(entityRegistry), componentRegistry(componentRegistry) {}

        template <typename T>
        void Entity::addComponent() noexcept {
            componentRegistry.add<T>(*this);
        }

        template <typename T>
        void Entity::removeComponent() noexcept {
            componentRegistry.remove<T>(*this);
        }

        template <typename T>
        const bool Entity::hasComponent() const noexcept {
            return componentRegistry.has<T>(*this);
        }

        bool Entity::operator==(const Entity& other) const {
            return id == other.id && &entityRegistry == &other.entityRegistry && &componentRegistry == &other.componentRegistry;
        }

        const Entity::ID Entity::getID() const { return id; }
    }  // namespace core::ecs
}  // namespace cobalt