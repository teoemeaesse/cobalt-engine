// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        Entity::Entity(const ID id, EntityRegistry& entityRegistry, ComponentRegistry& componentRegistry) noexcept
            : id(id), entityRegistry(entityRegistry), componentRegistry(componentRegistry) {}

        bool Entity::operator==(const Entity& other) const {
            return id == other.id && &entityRegistry == &other.entityRegistry && &componentRegistry == &other.componentRegistry;
        }

        const Entity::ID Entity::getID() const { return id; }
    }  // namespace core::ecs
}  // namespace cobalt