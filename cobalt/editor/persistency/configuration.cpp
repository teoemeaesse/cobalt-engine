//
// Created by tomas on 07-12-2023.
//

#include "editor/persistency/configuration.h"


namespace cobalt {
    namespace editor {
        CobaltConfiguration::CobaltConfiguration() : engine::Configuration(core::Path("cobalt-config.json", true)) {
        }

        core::Window CobaltConfiguration::createWindow() const {
            try {
                int width = get<int>("width");
                int height = get<int>("height");
                bool vsync = get<bool>("vsync");
                return core::WindowBuilder()
                    .setTitle("Cobalt")
                    .setWidth(width)
                    .setHeight(height)
                    .setVsync(vsync)
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
    }
}