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
                const engine::TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
                const engine::TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
                const engine::TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
                const engine::MaterialID woodMaterial = CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao);
                core::Material& material = CB_MATERIAL_LIBRARY.getMaterial(woodMaterial);
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

        class PanLeft : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanLeft(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panHorizontal(-1.0f);
            }
        };

        class PanRight : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanRight(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panHorizontal(1.0f);
            }
        };

        class PanUp : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanUp(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panVertical(1.0f);
            }
        };

        class PanDown : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanDown(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panVertical(-1.0f);
            }
        };

        class PanIn : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanIn(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panDepth(-1.0f);
            }
        };

        class PanOut : public core::ConcreteInputCommand<core::CameraController> {
            public:
            PanOut(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->panDepth(1.0f);
            }
        };

        class RotateY : public core::ConcreteInputCommand<core::CameraController> {
            public:
            RotateY(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->rotateVertical(-getInput().value * 0.005f);
            }
        };

        class RotateX : public core::ConcreteInputCommand<core::CameraController> {
            public:
            RotateX(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->rotateHorizontal(getInput().value * 0.005f);
            }
        };

        class Zoom : public core::ConcreteInputCommand<core::CameraController> {
            public:
            Zoom(core::CameraController* target) : core::ConcreteInputCommand<core::CameraController>(target) {
            }
            void execute() const override {
                getTarget()->zoom(-getInput().value * 5.0f);
            }
        };
    }
}