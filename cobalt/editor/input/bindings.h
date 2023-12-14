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

        class PanLeft : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanLeft(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panHorizontal(-1.0f);
            }
        };

        class PanRight : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanRight(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panHorizontal(1.0f);
            }
        };

        class PanUp : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanUp(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panVertical(1.0f);
            }
        };

        class PanDown : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanDown(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panVertical(-1.0f);
            }
        };

        class PanIn : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanIn(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panDepth(-1.0f);
            }
        };

        class PanOut : public core::ConcreteInputCommand<core::Camera> {
            public:
            PanOut(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->panDepth(1.0f);
            }
        };

        class RotateY : public core::ConcreteInputCommand<core::Camera> {
            public:
            RotateY(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->rotateVertical(-getInput().value * 0.005f);
            }
        };

        class RotateX : public core::ConcreteInputCommand<core::Camera> {
            public:
            RotateX(core::Camera* target) : core::ConcreteInputCommand<core::Camera>(target) {
            }
            void execute() const override {
                getTarget()->rotateHorizontal(getInput().value * 0.005f);
            }
        };

        class Zoom : public core::ConcreteInputCommand<core::PerspectiveCamera> {
            public:
            Zoom(core::PerspectiveCamera* target) : core::ConcreteInputCommand<core::PerspectiveCamera>(target) {
            }
            void execute() const override {
                getTarget()->zoom(-getInput().value * 5.0f);
            }
        };
    }
}