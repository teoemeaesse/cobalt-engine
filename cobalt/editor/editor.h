//
// Created
// by
// tomas
// on
// 17-12-2023.
//

#pragma once

#include "editor/persistency/cobalt_configuration.h"

namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor();
            ~Editor() override;

            void fixedTimeStep() override;
            void variableTimeStep(const float delta) override;
            void onResize(const uint width, const uint height) override;
            void bindInput();
            void createScene();

            private:
            CobaltConfiguration configuration;
            engine::DefaultGraph renderGraph;
            core::scene::Scene scene;
        };
    }  // namespace editor
}  // namespace cobalt