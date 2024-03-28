// Created by tomas on
// 28-03-2024

#pragma once

#include "core/ecs/plugin/bundle.h"
#include "engine/ecs/plugin/gfx/window.h"
#include "engine/ecs/plugin/input/input.h"
#include "engine/ecs/plugin/time/time.h"

namespace cobalt {
    namespace engine::ecs {
        class BaseBundle : public core::ecs::Bundle {
            public:
            BaseBundle() noexcept = default;
            virtual ~BaseBundle() noexcept = default;

            void addPlugins(core::ecs::World& world) noexcept override {
                world.addPlugin<InputPlugin>();
                world.addPlugin<TimePlugin>();
                world.addPlugin<WindowPlugin>();
            }
        };
    }  // namespace engine::ecs
}  // namespace cobalt