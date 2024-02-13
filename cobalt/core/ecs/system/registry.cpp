// Created by tomas on
// 13-02-2024

#include "core/ecs/system/registry.h"

namespace cobalt {
    namespace core::ecs {
        SystemRegistry::SystemRegistry(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept
            : systems(), entityRegistry(entityRegistry), resourceRegistry(resourceRegistry) {}

        void SystemRegistry::run() noexcept {
            for (auto& system : systems) {
                system->run();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt