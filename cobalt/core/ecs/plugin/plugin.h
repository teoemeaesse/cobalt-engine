/**
 * @file plugin.h
 * @brief A plugin is a group of ECS elements that work together to provide a specific functionality.
 * @author Tomás Marques
 * @date 08-02-2024
 */

#pragma once

#include "core/ecs/exception.h"

namespace cobalt {
    namespace core::ecs {
        class World;

        /**
         * @brief A Plugin is a collection of ECS elements such as Component's, Resource's and System's that work together to provide a specific
         * functionality. Plugins can also expose an API to be used by dependent plugins.
         * Two plugins are considered equal if their titles are equal, regardless of their description or dependencies. So you can override the
         * default engine plugins and add your own so long as the new API is compatible with the old one.
         */
        class Plugin {
            public:
            /**
             * @brief Create a new Plugin.
             * @param title The title of the plugin.
             * @param description The description of the plugin.
             * @param dependencies All the dependencies of the plugin.
             * @tparam Dependencies A list of dependency types for the plugin (must be children of Plugin).
             */
            template <typename... Dependencies>
            Plugin(const std::string& title, const std::string& description, Dependencies&&... dependencies) noexcept
                : dependencies{std::forward<Dependencies>(dependencies)...}, title(title), description(description) {
                static_assert((std::is_base_of_v<Plugin, Dependencies> && ...), "Dependencies must be of type Plugin.");
            }
            /**
             * @brief Default destructor.
             */
            virtual ~Plugin() = default;

            /**
             * @brief Equality operator for plugins. Compares the title of the plugins.
             * @param plugin Plugin to compare against.
             * @return True if the plugins are equal, false otherwise.
             */
            bool operator==(const Plugin& plugin) const noexcept;

            /**
             * @brief Add ECS elements to the world.
             * @param world The world to add the plugin to.
             */
            virtual void onPlug(World& world) const noexcept;

            /**
             * @brief Small log message to show that the plugin has been added to the world.
             */
            void log() const noexcept;

            /**
             * @brief Check if the dependencies of the plugin are met.
             * @param plugins A list of plugins to check against.
             * @return A list of missing dependencies. Empty if all the dependencies are met.
             */
            const Vec<std::string> findMissingDependencies(const Vec<Plugin>& plugins) const noexcept;

            /**
             * @brief Get the title for this plugin.
             * @return The title of the plugin.
             */
            const std::string& getTitle() const noexcept;

            private:
            const Vec<Plugin> dependencies;  ///< The dependencies of the plugin.
            std::string title;               ///< The title of the plugin.
            std::string description;         ///< The description of the plugin.
        };
    }  // namespace core::ecs
}  // namespace cobalt