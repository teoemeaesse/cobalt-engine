// Created by tomas on
// 16-04-2024

#pragma once

#include "engine/render/renderer.h"

namespace cobalt {
    namespace engine {
        class RenderPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Render";

            /**
             * @brief Construct the plugin.
             * @return RenderPlugin
             */
            RenderPlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt