// Created by tomas on
// 31-01-2024

#include "core/ecs/system/schedule.h"

namespace cobalt {
    namespace core::ecs {
        Schedule::Schedule(const World& world) noexcept : world(world) {}
    }  // namespace core::ecs
}  // namespace cobalt
