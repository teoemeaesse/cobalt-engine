/**
 * @file plugin.cpp
 * @brief A plugin for loading PBR materials.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#include "engine/material_pbr/plugin.h"

namespace cobalt {
    namespace engine {
        MaterialPBRPlugin::MaterialPBRPlugin() noexcept : Plugin(TITLE, "Provides PBR material creation and loading functionality.") {}

        void MaterialPBRPlugin::onPlug(core::ecs::World& world) const noexcept { world.registerComponent<MaterialPBR>(); }

        MaterialLibrary& getMaterialLibrary() noexcept {
            static MaterialLibrary library;
            return library;
        }
    }  // namespace engine
}  // namespace cobalt