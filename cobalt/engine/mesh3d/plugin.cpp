/**
 * @file plugin.h
 * @brief Plugin for loading 3D meshes.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#include "engine/mesh3d/plugin.h"

#include "engine/material/plugin.h"

namespace cobalt {
    namespace engine {
        Mesh3DPlugin::Mesh3DPlugin() noexcept : core::ecs::Plugin(TITLE, "Provides 3D mesh support.", MaterialPlugin{}) {}

        void Mesh3DPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt