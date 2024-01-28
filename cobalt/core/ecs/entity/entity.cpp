// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/entity.h"

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        Entity::Entity(const ID id, const Version version, EntityRegistry& entityRegistry, ComponentRegistry& componentRegistry) noexcept
            : id(id), version(version), entityRegistry(entityRegistry), componentRegistry(componentRegistry) {}

        Entity::Entity(Entity&& other) noexcept
            : id(other.id), version(other.version), entityRegistry(other.entityRegistry), componentRegistry(other.componentRegistry) {
            other.version = 0;
        }

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

        const bool Entity::isAlive() const noexcept { return entityRegistry.isAlive(*this); }

        bool Entity::operator==(const Entity& other) const {
            return id == other.id && version == other.version && &entityRegistry == &other.entityRegistry &&
                   &componentRegistry == &other.componentRegistry;
        }

        const Entity::ID Entity::getID() const { return id; }

        const Entity::Version Entity::getVersion() const { return version; }
    }  // namespace core::ecs
}  // namespace cobalt