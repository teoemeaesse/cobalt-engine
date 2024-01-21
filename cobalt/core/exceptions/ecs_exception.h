// Created by tomas on
// 21-01-2024

#pragma once

#include <stdexcept>

#include "core/ecs/entity/entity.h"

namespace cobalt {
    namespace core::ecs {
        template <typename T>
        class ComponentNotFoundException : public std::runtime_error {
            public:
            /** @brief: Create a new component not found exception.
             * @param entityID: The entity that was not found.
             * @return: The new component not found exception.
             */
            ComponentNotFoundException(const Entity::ID entityID)
                : std::runtime_error("Component not found for entity: " + std::to_string(entityID) + " with component: " + typeid(T).to_string()) {}
            ~ComponentNotFoundException() = default;
        };
    }  // namespace core::ecs
}  // namespace cobalt