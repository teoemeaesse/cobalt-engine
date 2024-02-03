// Created by tomas on
// 31-01-2024

#include "core/ecs/system/schedule.h"

namespace cobalt {
    namespace core::ecs {
        Schedule::Schedule(EntityRegistry& entityRegistry) noexcept : entityRegistry(entityRegistry) {}

        void Schedule::run() noexcept {
            for (auto& system : systems) {
                system->run();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt
