// Created by tomas on
// 16-04-2024

#include "engine/render/plugin.h"

namespace cobalt {
    namespace engine {
        RenderPlugin::RenderPlugin() noexcept
            : core::ecs::Plugin(TITLE, "Provides a general rendering API for a graph-based pipeline.", CameraPlugin{}) {}

        void RenderPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt