// Created by tomas on
// 21-01-2024

#pragma once

#include <stdexcept>

#include "core/ecs/component/component.h"
#include "core/ecs/properties.h"
#include "core/ecs/resource/resource.h"

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
                                     ") with component: " + Component::getTypeName<T>()) {}
            ~ComponentNotFoundException() = default;
        };

        template <typename T>
        class ResourceNotFoundException : public std::runtime_error {
            public:
            /**
             * @brief: Create a new resource not found exception.
             * @return: The new resource not found exception.
             */
            ResourceNotFoundException() : std::runtime_error("Resource not found: " + Resource::getTypeName<T>()) {}
            ~ResourceNotFoundException() = default;
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
                                     ") with component: " + Component::getTypeName<T>()) {}
            ~ComponentOverflowException() = default;
        };

        class PluginNotFoundException : public std::runtime_error {
            public:
            /**
             * @brief: Create a new plugin not found exception.
             * @return: The new plugin not found exception.
             */
            PluginNotFoundException(const std::string& pluginName) : std::runtime_error("Plugin not found: " + pluginName) {}
            ~PluginNotFoundException() = default;
        };
    }  // namespace core::ecs
}  // namespace cobalt