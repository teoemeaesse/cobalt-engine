// Created by tomas on
// 07-12-2023

#pragma once

#include "engine/cobalt.h"
#include "engine/window/plugin.h"

namespace cobalt {
    namespace editor {
        /**
         * @brief Stores the configuration for the editor.
         * Always loads from the default configuration file.
         */
        class CobaltConfiguration : public engine::Configuration {
            public:
            /**
             * @brief Create a new configuration from the default configuration file.
             * This must be in the same directory as the executable, and be named
             * "cobalt-config.json".
             * @return A new configuration.
             */
            CobaltConfiguration();
            /**
             * @brief Destroy the configuration.
             */
            ~CobaltConfiguration() = default;

            /**
             * @brief Create a new window from the configuration.
             * @return A new window.
             */
            engine::Window createWindow() const;

            /**
             * @brief Configure a window from the configuration.
             * @param window The window to configure.
             */
            void configureWindow(engine::Window& window) const;
        };
    }  // namespace editor
}  // namespace cobalt