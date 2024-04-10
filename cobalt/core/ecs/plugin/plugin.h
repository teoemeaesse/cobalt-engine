// Created by tomas on
// 08-02-2024

#pragma once

#include "core/ecs/exception.h"

namespace cobalt {
    namespace core::ecs {
        class World;

        /**
         * @brief: Collection of systems, components and resources that can be easily added to / removed from an ECS world for self-contained
         * functionality.
         */
        class Plugin {
            public:
            /**
             * @brief: Construct a plugin.
             * @param title: Title of the plugin.
             * @param description: Description of the plugin.
             * @param dependencies: Dependencies of the plugin.
             * @tparam Dependencies: List of dependency types for the plugin (must be child of Plugin).
             * @return: Plugin
             */
            template <typename... Dependencies>
            Plugin(const std::string& title, const std::string& description, Dependencies&&... dependencies) noexcept
                : dependencies{std::forward<Dependencies>(dependencies)...}, title(title), description(description) {
                static_assert((std::is_base_of_v<Plugin, Dependencies> && ...), "Dependencies must be of type Plugin.");
            }
            /**
             * @brief: Destruct a plugin.
             * @return: void
             */
            virtual ~Plugin() = default;

            /**
             * @brief: Equality operator for plugins. Compares the title of the plugins.
             * @param plugin: Plugin to compare against.
             * @return: bool
             */
            bool operator==(const Plugin& plugin) const noexcept;

            /**
             * @brief: Add systems, components and resources to the world.
             * @param world: World to add the plugin to.
             * @return: void
             */
            virtual void onPlug(World& world) const noexcept;

            /**
             * @brief: Small log message to show that the plugin has been added to the world.
             * @return: void
             */
            void log() const noexcept;

            /**
             * @brief: Check if the dependencies of the plugin are met.
             * @param plugins: List of plugins to check against.
             * @return: List of missing dependencies. Empty if all dependencies are met.
             */
            const Vec<std::string> findMissingDependencies(const Vec<Plugin>& plugins) const noexcept;

            /**
             * @brief: Get the title for this plugin.
             * @return: std::string
             */
            const std::string& getTitle() const noexcept;

            private:
            const Vec<Plugin> dependencies;
            std::string title;
            std::string description;
        };
    }  // namespace core::ecs
}  // namespace cobalt