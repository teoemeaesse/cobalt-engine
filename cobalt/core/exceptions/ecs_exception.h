// Created by tomas on
// 21-01-2024

#pragma once

#include <stdexcept>

#include "core/ecs/properties.h"

namespace cobalt {
    namespace core::ecs {
        template <typename T>
        class ComponentNotFoundException : public std::runtime_error {
            public:
            /** 
             * @brief: Create a new component not found exception.
             * @param entityID: The entity that was not found.
             * @return: The new component not found exception.
             */
            ComponentNotFoundException(const EntityProperties::ID entityID)
                : std::runtime_error("Component not found for entity (" + std::to_string(entityID) +
                                     ") with component: " + demangle(typeid(T).name())) {}
            ~ComponentNotFoundException() = default;
        };

        template <typename T>
        class ComponentOverflowException : public std::runtime_error {
            public:
            /** 
             * @brief: Create a new max components exceeded exception.
             * @return: The new max components exceeded exception.
             */
            ComponentOverflowException(const uint64 maxComponents)
                : std::runtime_error("Max components exceeded (" + std::to_string(maxComponents) +
                                     ") with component: " + demangle(typeid(T).name())) {}
            ~ComponentOverflowException() = default;
        };
    }  // namespace core::ecs
}  // namespace cobalt