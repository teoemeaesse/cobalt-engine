/**
 * @file entity.cpp
 * @brief Defines the Entity class, which is essentially a handle to a component mask in the ECS.
 * @author Tomás Marques
 * @date 19-01-2024
 */

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        Entity::Entity(const EntityProperties::ID id, const EntityProperties::Version version, EntityRegistry& entityRegistry,
                       ComponentRegistry& componentRegistry) noexcept
            : id(id), version(version), entityRegistry(entityRegistry), componentRegistry(componentRegistry) {}

        Entity::Entity(Entity&& other) noexcept
            : id(other.id), version(other.version), entityRegistry(other.entityRegistry), componentRegistry(other.componentRegistry) {
            other.version = 0;
        }

        void Entity::kill() const noexcept {
            componentRegistry.removeAll(id);
            entityRegistry.remove(*this);
        }

        const bool Entity::isAlive() const noexcept { return entityRegistry.isAlive(*this); }

        bool Entity::operator==(const Entity& other) const {
            return id == other.id && version == other.version && &entityRegistry == &other.entityRegistry &&
                   &componentRegistry == &other.componentRegistry;
        }

        const EntityProperties::ID Entity::getID() const { return id; }

        const EntityProperties::Version Entity::getVersion() const { return version; }
    }  // namespace core::ecs
}  // namespace cobalt