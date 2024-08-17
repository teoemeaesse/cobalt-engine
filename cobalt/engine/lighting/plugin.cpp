/**
 * @file plugin.cpp
 * @brief A lighting plugin to add lighting to a scene.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#include "engine/lighting/plugin.h"

namespace cobalt {
    namespace engine {
        LightingPlugin::LightingPlugin() noexcept
            : core::ecs::Plugin(TITLE, "Provides a set of lighting primitives such as point, directional and spot lights.") {}

        void LightingPlugin::onPlug(core::ecs::World& world) const noexcept {}
    }  // namespace engine
}  // namespace cobalt