// Created by tomas on
// 10-02-2024

#include "core/ecs/plugin/plugin.h"

#include "core/utils/log.h"

namespace cobalt {
    namespace core::ecs {
        Plugin::Plugin(const std::string& title, const std::string& description) noexcept : title(title), description(description) {}

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
            CB_CORE_INFO("Plugin added: {0}{1}{2}", formattedTitle, padding, description);
        }
    }  // namespace core::ecs
}  // namespace cobalt