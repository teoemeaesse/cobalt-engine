// Created by tomas on
// 10-02-2024

#include "engine/ecs/plugin/gfx/window.h"

#include "core/gl/context.h"
#include "engine/ecs/plugin/time/time.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        WindowPlugin::WindowPlugin() noexcept : Plugin(TITLE, "Provides window management functionality.", TimePlugin{}) {}

        void WindowPlugin::onPlug(World& world) const noexcept {
            world.registerEvent(FRAMEBUFFER_RESIZE_EVENT, FRAMEBUFFER_RESIZE_EVENT_DESCRIPTION);
            world.addResource(Move(
                createScope<core::gfx::Window>(core::gfx::WindowBuilder()
                                                   .setTitle("Cobalt")
                                                   .setWidth(1280)
                                                   .setHeight(720)
                                                   .setVsync(true)
                                                   .setFramebufferResizeCallback([](core::gfx::Window& window, const uint width, const uint height) {
                                                       static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())
                                                           ->triggerEvent(cobalt::engine::WindowPlugin::FRAMEBUFFER_RESIZE_EVENT);
                                                   })
                                                   .build())));

            world.addSystem<WriteRequest<core::gfx::Window>>(DefaultSchedules::Startup, [](auto window) {
                try {
                    window.get().init();
                } catch (const core::ecs::PluginNotFoundException& e) {
                    CB_CORE_WARN(e.what());
                }
            });
        }
    }  // namespace engine
}  // namespace cobalt