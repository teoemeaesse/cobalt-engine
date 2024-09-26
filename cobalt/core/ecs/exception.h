/**
 * @file exception.h
 * @brief Exceptions used by the ECS.
 * @author Tomás Marques
 * @date 21-01-2024
 */

#pragma once

#include <numeric>

#include "core/ecs/component/component.h"
#include "core/ecs/resource/resource.h"
#include "core/utils/exception.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Exception thrown when a component is requested but not found.
         */
        template <typename ComponentType, typename ThrowerType>
        class ComponentNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a ComponentNotFoundException.
             * @param entityID The entity (not) containing the component.
             */
            ComponentNotFoundException(const EntityProperties::ID entityID)
                : CoreException<ThrowerType>("Component not found for entity (" + std::to_string(entityID) +
                                             ") with component: " + Component::getTypeName<ComponentType>()) {}
        };

        /**
         * @brief Exception thrown when a resource is requested but not found.
         */
        template <typename ComponentType, typename ThrowerType>
        class ResourceNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a ResourceNotFoundException.
             */
            ResourceNotFoundException() : CoreException<ThrowerType>("Resource not found: " + Resource::getTypeName<ComponentType>()) {}
        };

        /**
         * @brief Exception thrown when a plugin is requested but not found.
         */
        template <typename ThrowerType>
        class PluginNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a PluginNotFoundException.
             * @param pluginName The name of the plugin that was not found.
             */
            PluginNotFoundException(const std::string& pluginName) : CoreException<ThrowerType>("Plugin not found: " + pluginName) {}
        };

        /**
         * @brief Exception thrown when a plugin dependency is not met.
         */
        template <typename ThrowerType>
        class PluginDependencyNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new plugin dependency not found exception.
             * @param pluginName The name of the plugin that has missing dependencies.
             * @param missingDependencies The names of the missing dependencies.
             */
            PluginDependencyNotFoundException(const std::string& pluginName, const std::vector<std::string>& missingDependencies)
                : CoreException<ThrowerType>(
                      "Plugin dependencies not met: " + pluginName + " -> " +
                      std::accumulate(missingDependencies.begin(), missingDependencies.end(), std::string{},
                                      [](const std::string& accum, const std::string& dep) { return accum.empty() ? dep : accum + ", " + dep; })) {}
        };

        /**
         * @brief Exception thrown when adding a component to an entity would exceed the maximum number of components per entity.
         */
        template <typename ComponentType, typename ThrowerType>
        class ComponentOverflowException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new max components exceeded exception.
             * @param maxComponents The maximum number of components per entity.
             */
            ComponentOverflowException(const u_int64_t maxComponents)
                : CoreException<ThrowerType>("Max components exceeded (" + std::to_string(maxComponents) +
                                             ") with component: " + Component::getTypeName<ComponentType>()) {}
        };

        /**
         * @brief Generic internal plugin exception.
         */
        template <typename PluginType, typename ThrowerType>
        class PluginException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a PluginException.
             * @param error The error message.
             */
            PluginException(const std::string& error)
                : CoreException<ThrowerType>("Plugin exception: " + demangle(typeid(PluginType).name()) + "\n\t-> " + error) {}
        };
    }  // namespace core::ecs
}  // namespace cobalt