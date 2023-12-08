//
// Created by tomas on 07-12-2023.
//

#pragma once

#include "engine/cobalt.h"


namespace cobalt {
    namespace editor {
        class Quit : public core::ConcreteInputCommand<engine::Application> {
            public:
            Quit(engine::Application* target) : core::ConcreteInputCommand<engine::Application>(target) {
            }
            void execute() const override {
                getTarget()->stop();
            }
        };

        class Fullscreen : public core::ConcreteInputCommand<core::Window> {
            public:
            Fullscreen(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->switchMode(core::WindowMode::Fullscreen);
                }
            }
        };

        class Borderless : public core::ConcreteInputCommand<core::Window> {
            public:
            Borderless(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->switchMode(core::WindowMode::Borderless);
                }
            }
        };

        class Windowed : public core::ConcreteInputCommand<core::Window> {
            public:
            Windowed(core::Window* target) : core::ConcreteInputCommand<core::Window>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->switchMode(core::WindowMode::Windowed);
                }
            }
        };
    }
}