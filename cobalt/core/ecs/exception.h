// Created by tomas on
// 21-01-2024

#pragma once

#include "core/ecs/component/component.h"
#include "core/ecs/resource/resource.h"
#include "core/exception.h"

namespace cobalt {
    namespace core::ecs {
        template <typename ComponentType, typename ThrowerType>
        class ComponentNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new component not found exception.
             * @param entityID The entity that was not found.
             */
            ComponentNotFoundException(const EntityProperties::ID entityID)
                : CoreException<ThrowerType>("Component not found for entity (" + std::to_string(entityID) +
                                             ") with component: " + Component::getTypeName<ComponentType>()) {}
        };

        template <typename ComponentType, typename ThrowerType>
        class ResourceNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new resource not found exception.
             */
            ResourceNotFoundException() : CoreException<ThrowerType>("Resource not found: " + Resource::getTypeName<ComponentType>()) {}
        };

        template <typename ComponentType, typename ThrowerType>
        class ComponentOverflowException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new max components exceeded exception.
             */
            ComponentOverflowException(const uint64 maxComponents)
                : CoreException<ThrowerType>("Max components exceeded (" + std::to_string(maxComponents) +
                                             ") with component: " + Component::getTypeName<ComponentType>()) {}
        };

        template <typename ThrowerType>
        class PluginNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new plugin not found exception.
             */
            PluginNotFoundException(const std::string& pluginName) : CoreException<ThrowerType>("Plugin not found: " + pluginName) {}
        };

        template <typename ThrowerType>
        class PluginDependencyNotFoundException : public CoreException<ThrowerType> {
            public:
            /**
             * @brief Create a new plugin dependency not found exception.
             */
            PluginDependencyNotFoundException(const std::string& pluginName, const Vec<std::string>& dependenciesMissing)
                : CoreException<ThrowerType>(
                      "Plugin dependencies not met: " + pluginName + " -> " +
                      std::accumulate(dependenciesMissing.begin(), dependenciesMissing.end(), std::string{},
                                      [](const std::string& accum, const std::string& dep) { return accum.empty() ? dep : accum + ", " + dep; })) {}
        };

        template <typename PluginType, typename ThrowerType>
        class PluginException : public CoreException<ThrowerType> {
            public:
            PluginException(const std::string& error)
                : CoreException<ThrowerType>("Plugin exception: " + demangle(typeid(PluginType).name()) + "\n\t-> " + error) {}
        };
    }  // namespace core::ecs
}  // namespace cobalt