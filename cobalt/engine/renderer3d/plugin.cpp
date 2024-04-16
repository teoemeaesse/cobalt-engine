// Created by tomas on
// 06-04-2024

#include "engine/renderer3d/plugin.h"

namespace cobalt {
    namespace engine {
        Renderer3DPlugin::Renderer3DPlugin() noexcept : core::ecs::Plugin(TITLE, "Adds a raster 3D renderer.") {}

        void Renderer3DPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt