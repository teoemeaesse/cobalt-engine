// Created by tomas on
// 19-01-2024

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        Entity::Entity(const ID id) : id(id) {}

        bool Entity::operator==(const Entity& other) const { return id == other.id; }

        void Entity::addComponent(const Component::ID id) { mask.set(id); }

        void Entity::removeComponent(const Component::ID id) { mask.reset(id); }

        const bool Entity::hasComponent(const Component::ID id) const { return mask.test(id); }

        const Entity::ID Entity::getID() const { return id; }
    }  // namespace core::ecs
}  // namespace cobalt