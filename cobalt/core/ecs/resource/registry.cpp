// Created by tomas on
// 12-02-2024

#include "core/ecs/resource/registry.h"

namespace cobalt {
    namespace core::ecs {
        void ResourceRegistry::add(Scope<Resource>&& resource) noexcept {
            const auto type = resource->getType();
            resources.erase(type);
            resources.emplace(type, Move(resource));
        }
    }  // namespace core::ecs
}  // namespace cobalt