/**
 * @file plugin.cpp
 * @brief A plugin is a group of ECS elements that work together to provide a specific functionality.
 * @author Tomás Marques
 * @date 10-02-2024
 */

#include "core/ecs/plugin/plugin.h"

#include "core/ecs/world.h"
#include "core/utils/log.h"

namespace cobalt {
    namespace core::ecs {
        bool Plugin::operator==(const Plugin& plugin) const noexcept { return title == plugin.title; }

        void Plugin::onPlug(World& world) const noexcept { CB_CORE_WARN("Plugin {0} does not define an onPlug method.", title); }

        void Plugin::log() const noexcept {
            const size_t titleWidth = 20;
            const size_t paddingWidth = 4;
            std::string formattedTitle = title;
            if (formattedTitle.length() > titleWidth) {
                formattedTitle = formattedTitle.substr(0, titleWidth - 3) + "...";
            } else {
                formattedTitle += std::string(titleWidth - formattedTitle.length(), ' ');
            }
            std::string padding(paddingWidth, ' ');
            CB_CORE_INFO("Plugin: {0}{1}{2}", formattedTitle, padding, description);
        }

        const std::vector<std::string> Plugin::findMissingDependencies(const std::vector<Plugin>& plugins) const noexcept {
            std::vector<std::string> missingDependencies;
            for (const auto& dependency : dependencies) {
                bool found = false;
                for (const auto& plugin : plugins) {
                    if (plugin == dependency) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    missingDependencies.emplace_back(dependency.getTitle());
                }
            }
            return missingDependencies;
        }

        const std::string& Plugin::getTitle() const noexcept { return title; }
    }  // namespace core::ecs
}  // namespace cobalt