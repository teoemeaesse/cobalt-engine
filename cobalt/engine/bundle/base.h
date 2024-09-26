// Created by tomas on
// 28-03-2024

#pragma once

#include "engine/camera/plugin.h"
#include "engine/input/plugin.h"
#include "engine/keyboard/plugin.h"
#include "engine/material/plugin.h"
#include "engine/mesh3d/plugin.h"
#include "engine/mouse/plugin.h"
#include "engine/raster3d/plugin.h"
#include "engine/render/plugin.h"
#include "engine/scene/plugin.h"
#include "engine/time/plugin.h"
#include "engine/window/plugin.h"

namespace cobalt {
    namespace engine {
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
                world.addPlugin<ScenePlugin>();
                world.addPlugin<MaterialPlugin>();
                world.addPlugin<RenderPlugin>();
                world.addPlugin<Renderer3DPlugin>();
                world.addPlugin<Mesh3DPlugin>();
                world.addPlugin<LightingPlugin>();
            }
        };
    }  // namespace engine
}  // namespace cobalt