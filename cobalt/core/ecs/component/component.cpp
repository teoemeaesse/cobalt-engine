// Created by tomas on
// 18-01-2024

#include "core/ecs/component/component.h"

namespace cobalt {
    namespace core::ecs {
        const ComponentProperties::Type Component::getType() noexcept {
            static const ComponentProperties::Type type = typeid(*this).hash_code();
            return type;
        }

        const std::string& Component::getTypeName() noexcept {
            static const std::string typeName = demangle(typeid(*this).name());
            return typeName;
        }

    }  // namespace core::ecs
}  // namespace cobalt