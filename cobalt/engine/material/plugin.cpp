/**
 * @file plugin.cpp
 * @brief A plugin for loading materials.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#include "engine/material/plugin.h"

namespace cobalt {
    namespace engine {
        MaterialPlugin::MaterialPlugin() noexcept : Plugin(TITLE, "Provides material creation, loading and managing functionality.") {}

        void MaterialPlugin::onPlug(core::ecs::World& world) const noexcept {
            world.registerComponent<MaterialID>();
            world.addResource<MaterialLibrary>();
        }

        MaterialLibrary& getMaterialLibrary(core::ecs::World& world) noexcept { return world.getResource<MaterialLibrary>(); }
    }  // namespace engine
}  // namespace cobalt