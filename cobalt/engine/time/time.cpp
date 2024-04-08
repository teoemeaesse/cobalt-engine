// Created by tomas on
// 08-02-2024

#include "engine/time/time.h"

namespace cobalt {
    using namespace core::ecs;

    namespace engine {
        Time::Time() noexcept : deltaTime(0.0f), elapsedTime(0.0f) {}

        float Time::getDeltaTime() const noexcept { return deltaTime; }

        float Time::getElapsedTime() const noexcept { return elapsedTime; }
    }  // namespace engine
}  // namespace cobalt