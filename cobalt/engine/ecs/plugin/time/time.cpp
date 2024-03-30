// Created by tomas on
// 08-02-2024

#include "engine/ecs/plugin/time/time.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        Time::Time() noexcept : deltaTime(0.0f), elapsedTime(0.0f) {}
    }  // namespace engine
}  // namespace cobalt