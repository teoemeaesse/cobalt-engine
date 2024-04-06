// Created by tomas on
// 06-04-2024

#include "engine/camera/plugin.h"

#include "core/ecs/world.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        CameraPlugin::CameraPlugin() noexcept : Plugin(TITLE, "Provides camera control and creation.") {}

        void CameraPlugin::onPlug(ecs::World& world) const noexcept { world.addResource<CameraManager>(); }
    }  // namespace engine
}  // namespace cobalt