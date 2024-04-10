// Created by tomas on
// 21-01-2024

#pragma once

#include "core/ecs/component/component.h"
#include "core/ecs/resource/resource.h"

namespace cobalt {
    namespace core::ecs {
        class ECSException : public std::runtime_error {
            public:
            /**
             * @brief Create a new ECS exception.
             * @param message The message of the exception.
             * @return ECSException
             */
            ECSException(const std::string& message) : std::runtime_error(message) {}
            /**
             * @brief Destruct the ECS exception.
             */
            ~ECSException() = default;
        };

        template <typename T>
        class ComponentNotFoundException : public ECSException {
            public:
            /**
             * @brief Create a new component not found exception.
             * @param entityID The entity that was not found.
             * @return The new component not found exception.
             */
            ComponentNotFoundException(const EntityProperties::ID entityID)
                : ECSException("Component not found for entity (" + std::to_string(entityID) + ") with component: " + Component::getTypeName<T>()) {}
            ~ComponentNotFoundException() = default;
        };

        template <typename T>
        class ResourceNotFoundException : public ECSException {
            public:
            /**
             * @brief Create a new resource not found exception.
             * @return The new resource not found exception.
             */
            ResourceNotFoundException() : ECSException("Resource not found: " + Resource::getTypeName<T>()) {}
            ~ResourceNotFoundException() = default;
        };

        template <typename T>
        class ComponentOverflowException : public ECSException {
            public:
            /**
             * @brief Create a new max components exceeded exception.
             * @return The new max components exceeded exception.
             */
            ComponentOverflowException(const uint64 maxComponents)
                : ECSException("Max components exceeded (" + std::to_string(maxComponents) + ") with component: " + Component::getTypeName<T>()) {}
            ~ComponentOverflowException() = default;
        };

        class PluginNotFoundException : public ECSException {
            public:
            /**
             * @brief Create a new plugin not found exception.
             * @return The new plugin not found exception.
             */
            PluginNotFoundException(const std::string& pluginName) : ECSException("Plugin not found: " + pluginName) {}
            ~PluginNotFoundException() = default;
        };

        class PluginDependencyNotFoundException : public ECSException {
            public:
            /**
             * @brief Create a new plugin dependency not found exception.
             * @return The new plugin dependency not found exception.
             */
            PluginDependencyNotFoundException(const std::string& pluginName, const Vec<std::string>& dependenciesMissing)
                : ECSException(
                      "Plugin dependencies not met: " + pluginName + " -> " +
                      std::accumulate(dependenciesMissing.begin(), dependenciesMissing.end(), std::string{},
                                      [](const std::string& accum, const std::string& dep) { return accum.empty() ? dep : accum + ", " + dep; })) {}
            ~PluginDependencyNotFoundException() = default;
        };

        template <typename T>
        class PluginException : public ECSException {
            public:
            PluginException(const std::string& error) : ECSException("Plugin exception: " + demangle(typeid(T).name()) + "\n\t-> " + error) {}
        };
    }  // namespace core::ecs
}  // namespace cobalt