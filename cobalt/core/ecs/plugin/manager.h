// Created by tomas on
// 24-03-2024

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace core::ecs {
        class PluginManager {
            public:
            /**
             * @brief: Default constructor.
             * @return: PluginManager instance.
             */
            PluginManager() noexcept = default;
            /**
             * @brief: Default destructor.
             * @return: void
             */
            ~PluginManager() noexcept = default;

            /**
             * @brief: Add a plugin to the manager.
             * @param plugin: Plugin to add.
             * @return: void
             */
            void addPlugin(const Plugin& plugin) noexcept;
            /**
             * @brief: Check if a plugin is registered in the manager.
             * @param plugin: Plugin to check.
             * @return: bool
             */
            bool isPlugin(const Plugin& plugin) noexcept;
            /**
             * @brief: Check if a plugin is registered in the manager.
             * @param title: Title of the plugin to check.
             * @return: bool
             */
            bool isPlugin(const std::string& title) noexcept;
            /**
             * @brief: Check if the dependencies of all the plugins are met.
             * @return: void
             */
            void checkDependencies();

            private:
            Vec<Plugin> plugins;
        };
    }  // namespace core::ecs
}  // namespace cobalt
