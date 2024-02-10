// Created by tomas on
// 08-02-2024

#include "engine/ecs/plugin/time.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        Time::Time() noexcept : deltaTime(0.0f), elapsedTime(0.0f) {}

        TimePlugin::TimePlugin() noexcept : Plugin("Time", "Provides delta time for frame interpolation and timer support.") {}

        void TimePlugin::onPlug(core::ecs::World& world) const noexcept { world.addResource<Time>(); }
    }  // namespace engine
}  // namespace cobalt