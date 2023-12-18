//
// Created by tomas on 07-12-2023.
//

#pragma once

#include "engine/cobalt.h"
#include "editor/editor.h"


namespace cobalt {
    namespace editor {
        class Spawn : public core::ConcreteInputCommand<core::Scene> {
            public:
            Spawn(core::Scene* target) : core::ConcreteInputCommand<core::Scene>(target) {
            }
            void execute() const override {
                if (getInput().held || !getInput().active)
                    return;
                static int i = 2;
                core::Material* material = new core::Material(
                    CB_SHADER_LIBRARY.getShader(CB_SHADER_LIBRARY.getShaderID("scene_shader")),
                    CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-albedo")),
                    CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-normal")),
                    CB_TEXTURE_LIBRARY.getTexture2D(CB_TEXTURE_LIBRARY.getTextureID("wood-mrao"))
                );
                core::Mesh sphere = core::Mesh::createSphere(5.0f, material);
                sphere.translate(glm::vec3(10.0f * i++, 0.0f, 0.0f));
                getTarget()->addMesh(std::move(sphere));
            }
        };
        class Quit : public core::ConcreteInputCommand<Editor> {
            public:
            Quit(Editor* target) : core::ConcreteInputCommand<Editor>(target) {
            }
            void execute() const override {
                getTarget()->stop();
            }
        };

        class Fullscreen : public core::ConcreteInputCommand<Editor> {
            public:
            Fullscreen(Editor* target) : core::ConcreteInputCommand<Editor>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::WindowMode::Fullscreen);
                    getTarget()->createScene();
                }
            }
        };

        class Borderless : public core::ConcreteInputCommand<Editor> {
            public:
            Borderless(Editor* target) : core::ConcreteInputCommand<Editor>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::WindowMode::Borderless);
                    getTarget()->createScene();
                }
            }
        };

        class Windowed : public core::ConcreteInputCommand<Editor> {
            public:
            Windowed(Editor* target) : core::ConcreteInputCommand<Editor>(target) {
            }
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::WindowMode::Windowed);
                    getTarget()->createScene();
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