// Created by tomas on
// 06-04-2024

#include "engine/raster3d/plugin.h"

#include "engine/mesh3d/plugin.h"
#include "engine/render/plugin.h"

namespace cobalt {
    namespace engine {
        Renderer3DPlugin::Renderer3DPlugin() noexcept : core::ecs::Plugin(TITLE, "Adds a 3D rasterized renderer.", RenderPlugin{}, Mesh3DPlugin{}) {}

        void Renderer3DPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt
