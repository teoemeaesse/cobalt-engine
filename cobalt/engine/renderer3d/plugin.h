// Created by tomas on
// 06-04-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "engine/renderer3d/renderer.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief 3D renderer plugin. Allows rendering 3D meshes.
         */
        class Renderer3DPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Renderer3D";

            /**
             * @brief Construct the plugin.
             * @return Renderer3DPlugin
             */
            Renderer3DPlugin() noexcept;

            /**
             * @brief Initialize the plugin.
             * @param world World instance.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt