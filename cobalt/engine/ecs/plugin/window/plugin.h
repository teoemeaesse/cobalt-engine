// Created by tomas on
// 08-02-2024

#pragma once

#include "core/gfx/window.h"
#include "core/gl/context.h"
#include "engine/ecs/plugin/time/plugin.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Window plugin. Adds the window resource to the world.
         */
        class WindowPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Window";

            static inline constexpr const char* FRAMEBUFFER_RESIZE_EVENT = "WindowResize";
            static inline constexpr const char* FRAMEBUFFER_RESIZE_EVENT_DESCRIPTION = "Called whenever the window is resized.";

            /**
             * @brief: Construct the plugin.
             * @return: WindowPlugin
             */
            WindowPlugin() noexcept : Plugin(TITLE, "Provides window management functionality.", TimePlugin{}) {}

            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override {
                world.registerEvent(FRAMEBUFFER_RESIZE_EVENT, FRAMEBUFFER_RESIZE_EVENT_DESCRIPTION);
                world.addResource(Move(createScope<core::gfx::Window>(
                    core::gfx::WindowBuilder()
                        .setTitle("Cobalt")
                        .setWidth(1280)
                        .setHeight(720)
                        .setVsync(true)
                        .setFramebufferResizeCallback([](core::gfx::Window& window, const uint width, const uint height) {
                            static_cast<core::ecs::World*>(core::gl::Context::getUserPointer())
                                ->triggerEvent(cobalt::engine::WindowPlugin::FRAMEBUFFER_RESIZE_EVENT);
                        })
                        .build())));

                world.addSystem<core::ecs::WriteRequest<core::gfx::Window>>(core::ecs::DefaultSchedules::Startup, [](auto window) {
                    try {
                        window.get().init();
                    } catch (const core::ecs::PluginNotFoundException& e) {
                        CB_CORE_WARN(e.what());
                    }
                });
            }
        };
    }  // namespace engine
}  // namespace cobalt