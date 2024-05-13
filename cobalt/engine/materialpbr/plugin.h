/**
 * @file plugin.h
 * @brief A plugin for loading PBR materials.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"
#include "engine/materialpbr/material.h"

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
    }  // namespace engine
}  // namespace cobalt