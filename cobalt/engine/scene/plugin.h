// Created by tomas on
// 10-04-2024

#pragma once

#include "engine/scene/scene.h"

namespace cobalt {
    namespace engine {
        class ScenePlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Scene";

            /**
             * @brief Construct the plugin.
             * @return ScenePlugin
             */
            ScenePlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt