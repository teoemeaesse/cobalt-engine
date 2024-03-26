// Created by tomas on
// 08-02-2024

#pragma once

#include "core/ecs/world.h"
#include "core/gfx/window.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Window plugin. Adds the window resource to the world.
         */
        class WindowPlugin : public core::ecs::Plugin {
            public:
            constexpr static const char* Title = "Window";

            constexpr static const char* FramebufferResizeEvent = "WindowResize";
            constexpr static const char* FramebufferResizeEventDescription = "Called whenever the window is resized.";

            /**
             * @brief: Construct the plugin.
             * @return: WindowPlugin
             */
            WindowPlugin() noexcept;

            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt