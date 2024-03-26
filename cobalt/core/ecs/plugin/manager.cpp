// Created by tomas on
// 24-03-2024

#include "core/ecs/plugin/manager.h"

#include "core/ecs/exception.h"

namespace cobalt {
    namespace core::ecs {
        void PluginManager::addPlugin(const Plugin& plugin) noexcept {
            if (!isPlugin(plugin)) {
                plugins.emplace_back(plugin);
            }
        }

        bool PluginManager::isPlugin(const Plugin& plugin) noexcept {
            for (const auto& registered : plugins) {
                if (registered == plugin) {
                    return true;
                }
            }
            return false;
        }

        bool PluginManager::isPlugin(const std::string& title) noexcept {
            for (const auto& plugin : plugins) {
                if (plugin.getTitle() == title) {
                    return true;
                }
            }
            return false;
        }

        void PluginManager::checkDependencies() {
            for (const auto& plugin : plugins) {
                const auto missing = plugin.findMissingDependencies(plugins);
                if (!missing.empty()) {
                    throw PluginDependencyNotFoundException(plugin.getTitle(), missing);
                }
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt
