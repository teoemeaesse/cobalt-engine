// Created by tomas on
// 10-02-2024

#include "engine/ecs/plugin/window.h"

#include "core/gl/context.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        WindowPlugin::WindowPlugin() noexcept : Plugin("Window", "Provides window management functionality.") {}

        void WindowPlugin::onPlug(World& world) const noexcept {
            world.addResource(Move(createScope<core::gfx::Window>(Move(
                core::gfx::WindowBuilder()
                    .setTitle("Cobalt")
                    .setWidth(1280)
                    .setHeight(720)
                    .setVsync(true)
                    .setFramebufferResizeCallback(
                        [](core::gfx::Window& window, const uint width, const uint height) { window.getDefaultFBO().resize(width, height); })
                    .setResizeCallback([](core::gfx::Window& window, const uint width, const uint height) { window.setDimensions(width, height); })
                    .build()))));

            // TODO: Add commands to ECS so i can run this code in a system
            world.getResource<core::gfx::Window>().init();
        }
    }  // namespace engine
}  // namespace cobalt