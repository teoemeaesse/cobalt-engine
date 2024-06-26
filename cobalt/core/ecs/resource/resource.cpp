/**
 * @file resource.cpp
 * @brief A Resource is an ECS element consisting of a piece of structured data that can be shared between systems.
 * @author Tomás Marques
 * @date 03-02-2024
 */

#include "core/ecs/resource/resource.h"

namespace cobalt {
    namespace core::ecs {
        const ResourceProperties::Type Resource::getType() const noexcept {
            static const ResourceProperties::Type type = typeid(*this).hash_code();
            return type;
        }

        const std::string& Resource::getTypeName() const noexcept {
            static const std::string typeName = demangle(typeid(*this).name());
            return typeName;
        }
    }  // namespace core::ecs
}  // namespace cobalt