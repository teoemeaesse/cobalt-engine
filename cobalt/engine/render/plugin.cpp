// Created by tomas on
// 16-04-2024

#include "engine/render/plugin.h"

#include "engine/mesh3d/plugin.h"

namespace cobalt {
    namespace engine {
        RenderPlugin::RenderPlugin() noexcept
            : core::ecs::Plugin(TITLE, "Provides a general rendering API for a graph-based pipeline.", CameraPlugin{}, Mesh3DPlugin{}) {}

        void RenderPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt