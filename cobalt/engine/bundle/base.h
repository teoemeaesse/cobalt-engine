// Created by tomas on
// 28-03-2024

#pragma once

#include "core/ecs/plugin/bundle.h"
#include "engine/camera/plugin.h"
#include "engine/input/plugin.h"
#include "engine/keyboard/plugin.h"
#include "engine/mouse/plugin.h"
#include "engine/time/plugin.h"
#include "engine/window/plugin.h"

namespace cobalt {
    namespace engine::ecs {
        class BaseBundle : public core::ecs::Bundle {
            public:
            BaseBundle() noexcept = default;
            virtual ~BaseBundle() noexcept = default;

            void addPlugins(core::ecs::World& world) noexcept override {
                world.addPlugin<InputPlugin>();
                world.addPlugin<KeyboardPlugin>();
                world.addPlugin<MousePlugin>();
                world.addPlugin<WindowPlugin>();
                world.addPlugin<TimePlugin>();
                world.addPlugin<CameraPlugin>();
            }
        };
    }  // namespace engine::ecs
}  // namespace cobalt