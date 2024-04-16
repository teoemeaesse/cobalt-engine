// Created by tomas on
// 16-04-2024

#include "engine/render/plugin.h"

#include "engine/renderer3d/plugin.h"

namespace cobalt {
    namespace engine {
        RenderPlugin::RenderPlugin() noexcept : core::ecs::Plugin(TITLE, "General rendering API", Renderer3DPlugin{}) {}

        void RenderPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt