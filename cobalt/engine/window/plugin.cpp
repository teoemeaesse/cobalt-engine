// Created by tomas on
// 06-04-2024

#include "engine/time/plugin.h"

#include "core/gl/context.h"
#include "engine/window/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        WindowPlugin::WindowPlugin() noexcept : Plugin(TITLE, "Provides window management functionality.", TimePlugin{}) {}

        void WindowPlugin::onPlug(ecs::World& world) const noexcept {
            world.registerEvent(FRAMEBUFFER_RESIZE_EVENT, FRAMEBUFFER_RESIZE_EVENT_DESCRIPTION);

            world.addResource<gfx::Window>(Move(gfx::Window::create(
                gfx::WindowProperties().setTitle("Cobalt").setWidth(1280).setHeight(720).setVsync(true).setFramebufferResizeCallback(
                    [](gfx::Window& window, const uint width, const uint height) {
                        static_cast<ecs::World*>(gl::Context::getUserPointer())->triggerEvent(WindowPlugin::FRAMEBUFFER_RESIZE_EVENT);
                    }))));

            // world.addSystem<ecs::WriteRequest<gfx::Window>>(ecs::DefaultSchedules::Startup, [](auto window) {
            //     try {
            //         window.get().init();
            //     } catch (const ecs::PluginNotFoundException& e) {
            //         CB_CORE_WARN(e.what());
            //     }
            // });
        }
    }  // namespace engine
}  // namespace cobalt