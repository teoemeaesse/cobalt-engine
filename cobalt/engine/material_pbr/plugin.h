/**
 * @file plugin.h
 * @brief A plugin for loading PBR materials.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#pragma once

#include "core/ecs/world.h"
#include "engine/material_pbr/library.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A plugin for loading PBR materials.
         */
        class MaterialPBRPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Material PBR";

            /**
             * @brief Create the plugin.
             */
            MaterialPBRPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };

        /**
         * @brief Returns the global material library.
         * @return The material library.
         */
        MaterialLibrary& getMaterialLibrary() noexcept;
    }  // namespace engine
}  // namespace cobalt