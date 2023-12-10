//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/cobalt_configuration.h"


namespace cobalt {
    namespace editor {
        CobaltConfiguration::CobaltConfiguration() : engine::Configuration(core::Path("cobalt-config.json", true)) {
        }

        core::Window CobaltConfiguration::createWindow() const {
            try {
                int width = get<int>("width");
                int height = get<int>("height");
                bool vsync = get<bool>("vsync");
                core::WindowMode mode = static_cast<core::WindowMode>(get<int>("mode"));
                return core::WindowBuilder()
                    .setTitle("Cobalt")
                    .setWidth(width)
                    .setHeight(height)
                    .setVsync(vsync)
                    .setMode(mode)
                    .build();
            } catch (const engine::ConfigurationException& e) {
                CB_WARN("Failed to load Cobalt configuration: {}", e.what());
                return core::WindowBuilder()
                    .setTitle("Cobalt")
                    .setWidth(800)
                    .setHeight(600)
                    .setVsync(false)
                    .build();
            }
        }

        void CobaltConfiguration::configureWindow(core::Window& window) const {
            try {
                int width = get<int>("width");
                int height = get<int>("height");
                bool vsync = get<bool>("vsync");
                core::WindowMode mode = static_cast<core::WindowMode>(get<int>("mode"));
                window.setDimensions(width, height);
                window.setVsync(vsync);
                window.setMode(mode);
            } catch (const engine::ConfigurationException& e) {
                CB_WARN("Failed to load Cobalt configuration: {}", e.what());
                window.setDimensions(800, 600);
                window.setVsync(false);
            }
        }
    }
}