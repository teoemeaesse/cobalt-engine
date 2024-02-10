// Created by tomas on
// 08-02-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Time resource.
         * @param deltaTime: Time since last frame (seconds).
         * @param elapsedTime: Time since application startup (seconds).
         */
        struct Time : public core::ecs::Resource {
            Time() noexcept;

            float deltaTime;
            float elapsedTime;
        };

        class TimePlugin : public core::ecs::Plugin {
            public:
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt