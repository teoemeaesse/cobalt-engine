// Created by tomas on
// 17-12-2023

#pragma once

#include "editor/persistency/cobalt_configuration.h"
#include "engine/bundle/base.h"

namespace cobalt {
    namespace editor {
        class Editor : public engine::Application {
            public:
            Editor();
            ~Editor() override;

            void setup() override;

            void addPlugins() override;
            void fixedTimeStep() override;
            void variableTimeStep(const float delta) override;
            void bindInput();
            void createScene();

            private:
            CobaltConfiguration configuration;
        };
    }  // namespace editor
}  // namespace cobalt