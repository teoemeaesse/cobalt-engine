// Created by tomas on
// 07-12-2023

#include "editor/persistency/cobalt_configuration.h"

namespace cobalt {
    namespace editor {
        CobaltConfiguration::CobaltConfiguration() : engine::Configuration(core::io::Path("cobalt-config.json", true)) {}

        core::gfx::Window CobaltConfiguration::createWindow() const {
            try {
                int width = get<int>("width");
                int height = get<int>("height");
                bool vsync = get<bool>("vsync");
                core::gfx::WindowMode mode = static_cast<core::gfx::WindowMode>(get<int>("mode"));
                return core::gfx::Window::create(
                    core::gfx::WindowProperties().setTitle("Cobalt").setWidth(width).setHeight(height).setVsync(vsync).setMode(mode));
            } catch (const engine::ConfigurationException& e) {
                CB_WARN("Failed to load Cobalt configuration: {}", e.what());
                return core::gfx::Window::create(core::gfx::WindowProperties().setTitle("Cobalt").setWidth(800).setHeight(600).setVsync(false));
            }
        }

        void CobaltConfiguration::configureWindow(core::gfx::Window& window) const {
            try {
                int width = get<int>("width");
                int height = get<int>("height");
                bool vsync = get<bool>("vsync");
                core::gfx::WindowMode mode = static_cast<core::gfx::WindowMode>(get<int>("mode"));
                window.setDimensions(width, height);
                window.resize();
                window.setVsync(vsync);
                window.setMode(mode);
            } catch (const engine::ConfigurationException& e) {
                CB_WARN("Failed to load Cobalt configuration: {}", e.what());
                window.setDimensions(800, 600);
                window.resize();
                window.setVsync(false);
            }
        }
    }  // namespace editor
}  // namespace cobalt