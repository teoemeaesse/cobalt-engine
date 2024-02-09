// Created by tomas on
// 08-02-2024

#include "engine/ecs/plugin/time.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        Time::Time() noexcept : deltaTime(0.0f), timeSinceStartup(0.0f) {}

        void TimePlugin::onPlug(core::ecs::World& world) const noexcept { world.addResource<Time>(); }
    }  // namespace engine
}  // namespace cobalt