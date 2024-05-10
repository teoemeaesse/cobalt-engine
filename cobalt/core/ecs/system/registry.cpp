/**
 * @file registry.h
 * @brief Storage for every system in the ECS.
 * @author Tomás Marques
 * @date 13-02-2024
 */

#include "core/ecs/system/registry.h"

namespace cobalt {
    namespace core::ecs {
        SystemRegistry::SystemRegistry(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                                       EventManager& eventManager) noexcept
            : systems(),
              entityRegistry(entityRegistry),
              resourceRegistry(resourceRegistry),
              systemManager(systemManager),
              eventManager(eventManager) {}

        void SystemRegistry::run() noexcept {
            for (auto& system : systems) {
                system->run();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt