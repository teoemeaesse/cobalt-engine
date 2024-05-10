/**
 * @file manager.h
 * @brief A manager for plugins that can be added to a world.
 * @author Tomás Marques
 * @date 23-03-2024
 */

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief A manager for plugins that can be added to a world. Provides an interface to manage plugins and check their dependencies.
         */
        class PluginManager {
            public:
            /**
             * @brief Default constructor.
             */
            PluginManager() noexcept = default;
            /**
             * @brief Default destructor.
             */
            ~PluginManager() noexcept = default;

            /**
             * @brief Adds a Plugin to the manager.
             * @param plugin The Plugin to add.
             */
            void addPlugin(const Plugin& plugin) noexcept;

            /**
             * @brief Checks if a Plugin is registered with the manager.
             * @param plugin The Plugin to check.
             * @return True if the Plugin is registered, false otherwise.
             */
            bool isPlugin(const Plugin& plugin) const noexcept;
            /**
             * @brief Checks if a Plugin is registered with the manager.
             * @param title The title of the Plugin to check.
             * @return True if the Plugin is registered, false otherwise.
             */
            bool isPlugin(const std::string& title) const noexcept;

            /**
             * @brief Checks if the dependencies of all the plugins are met.
             * @throws PluginDependencyNotFoundException If a dependency is not met.
             */
            void checkDependencies() const;

            private:
            Vec<Plugin> plugins;
        };
    }  // namespace core::ecs
}  // namespace cobalt
