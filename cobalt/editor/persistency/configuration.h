//
// Created by tomas on 07-12-2023.
//

#pragma once

#include "engine/cobalt.h"


namespace cobalt {
    namespace editor {
        /* Stores the configuration for the editor.
         * Always loads from the default configuration file.
         */
        class CobaltConfiguration : public engine::Configuration {
            public:
            /* Create a new configuration from the default configuration file.
             * This must be in the same directory as the executable, and be named
             * "cobalt-config.json".
             * @return: A new configuration.
             */
            CobaltConfiguration();
            /* Destroy the configuration.
             */
            ~CobaltConfiguration() = default;
            
            /* Create a new window from the configuration.
             * @return: A new window.
             */
            core::Window createWindow() const;
        };
    }
}