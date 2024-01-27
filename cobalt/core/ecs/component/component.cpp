// Created by tomas on
// 18-01-2024

#include "core/ecs/component/component.h"

namespace cobalt {
    namespace core::ecs {
        Component::Component(const ID id) noexcept : id(id), type(0) {}

        const Component::Type Component::getType() noexcept {
            if (type == 0) {
                type = typeid(*this).hash_code();
            }
            return type;
        }
    }  // namespace core::ecs
}  // namespace cobalt