// Created by tomas on
// 13-02-2024

#include "core/ecs/system/commands.h"

namespace cobalt {
    namespace core::ecs {
        Commands::Commands(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept
            : SystemParameter(entityRegistry, resourceRegistry, systemManager) {}

        Entity& Commands::spawn() noexcept { return entityRegistry.add(); }
    }  // namespace core::ecs
}  // namespace cobalt