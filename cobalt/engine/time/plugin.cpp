// Created by tomas on
// 06-04-2024

#include "engine/time/plugin.h"

#include "engine/time/time.h"

namespace cobalt {
    namespace engine {
        TimePlugin::TimePlugin() noexcept : Plugin(TITLE, "Provides delta time for frame interpolation and timer support.") {}

        void TimePlugin::onPlug(core::ecs::World& world) const noexcept { world.addResource<Time>(); }
    }  // namespace engine
}  // namespace cobalt