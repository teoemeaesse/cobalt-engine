// Created by tomas on
// 14-02-2024

#include "core/ecs/event/event.h"

namespace cobalt {
    namespace core::ecs {
        Event::Event(const std::string& name, const std::string& description) noexcept : name(name), description(description) {}

        bool Event::operator==(const Event& other) const noexcept { return name == other.name && description == other.description; }

        void Event::log() const noexcept {
            const size_t nameWidth = 20;
            const size_t paddingWidth = 4;
            std::string formattedName = name;
            if (formattedName.length() > nameWidth) {
                formattedName = formattedName.substr(0, nameWidth - 3) + "...";
            } else {
                formattedName += std::string(nameWidth - formattedName.length(), ' ');
            }
            std::string padding(paddingWidth, ' ');
            CB_CORE_INFO("Event: {0}{1}{2}", formattedName, padding, description);
        }

        const std::string& Event::getName() const noexcept { return name; }
    }  // namespace core::ecs
}  // namespace cobalt