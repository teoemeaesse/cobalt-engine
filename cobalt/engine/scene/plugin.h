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
             */
            ScenePlugin() noexcept;

            /**
             * @brief Initializes the plugin.
             * @param world World to plug into.
             */
            void onPlug(core::ecs::World& world) const noexcept override;

            /**
             * @brief Adds a new scene graph to the world.
             * @return The entity representing the scene graph.
             */
            static core::ecs::Entity& addGraph(core::ecs::World& world) noexcept;
        };
    }  // namespace engine
}  // namespace cobalt