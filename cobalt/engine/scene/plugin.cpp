// Created by tomas on
// 10-04-2024

#include "engine/scene/plugin.h"

#include "core/ecs/world.h"
#include "engine/camera/plugin.h"
#include "engine/lighting/plugin.h"

namespace cobalt {
    namespace engine {
        ScenePlugin::ScenePlugin() noexcept : core::ecs::Plugin(TITLE, "Provides scene graph functionality.", CameraPlugin{}, LightingPlugin{}) {}

        void ScenePlugin::onPlug(core::ecs::World& world) const noexcept { world.addResource<Scene>(world); }
    }  // namespace engine
}  // namespace cobalt