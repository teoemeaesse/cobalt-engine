/**
 * @file plugin.h
 * @brief A plugin for loading materials.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#pragma once

#include "core/ecs/world.h"
#include "engine/material/library.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A plugin for loading materials.
         */
        class MaterialPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Material";

            /**
             * @brief Create the plugin.
             */
            MaterialPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };

        /**
         * @brief Returns the global material library.
         * @param world The world to get the material library from.
         * @return The material library.
         */
        MaterialLibrary& getMaterialLibrary(core::ecs::World& world) noexcept;
    }  // namespace engine
}  // namespace cobalt