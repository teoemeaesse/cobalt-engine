// Created by tomas on
// 13-02-2024

#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        SystemParameter::SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept
            : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry), systemManager(systemManager) {}
    }  // namespace core::ecs
}  // namespace cobalt