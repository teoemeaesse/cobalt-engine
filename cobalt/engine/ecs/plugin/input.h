// Created by tomas on
// 10-02-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"

namespace cobalt {
    namespace engine {

        class InputPlugin : public core::ecs::Plugin {
            public:
            /**
             * @brief: Initializes the plugin.
             * @param world: World to plug into.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt