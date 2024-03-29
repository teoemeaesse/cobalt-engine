// Created by tomas on
// 07-12-2023

#pragma once

#include "editor/editor.h"

namespace cobalt {
    namespace editor {
        class Spawn : public core::input::ConcreteInputCommand<core::scene::Scene> {
            public:
            Spawn(core::ecs::World& world, core::scene::Scene* target) : core::input::ConcreteInputCommand<core::scene::Scene>(world, target) {}
            void execute() const override {
                if (getInput().held || !getInput().active) return;
                static int i = 2;
                const engine::TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
                const engine::TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
                const engine::TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
                const engine::MaterialID woodMaterial = CB_MATERIAL_LIBRARY.makePBR("wood", woodAlbedo, woodNormal, woodMrao);
                core::gfx::Material& material = CB_MATERIAL_LIBRARY.getMaterial(woodMaterial);
                core::gfx::Mesh sphere = core::gfx::MeshFactory::createSphere(5.0f, material);
                sphere.translate(glm::vec3(10.0f * i++, 0.0f, 0.0f));
                getTarget()->addMesh(Move(sphere));
            }
        };
        class Quit : public core::input::ConcreteInputCommand<Editor> {
            public:
            Quit(core::ecs::World& world, Editor* target) : core::input::ConcreteInputCommand<Editor>(world, target) {}
            void execute() const override { getTarget()->stop(); }
        };

        class Fullscreen : public core::input::ConcreteInputCommand<Editor> {
            public:
            Fullscreen(core::ecs::World& world, Editor* target) : core::input::ConcreteInputCommand<Editor>(world, target) {}
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::gfx::WindowMode::Fullscreen);
                    getTarget()->createScene();
                }
            }
        };

        class Borderless : public core::input::ConcreteInputCommand<Editor> {
            public:
            Borderless(core::ecs::World& world, Editor* target) : core::input::ConcreteInputCommand<Editor>(world, target) {}
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::gfx::WindowMode::Borderless);
                    getTarget()->createScene();
                }
            }
        };

        class Windowed : public core::input::ConcreteInputCommand<Editor> {
            public:
            Windowed(core::ecs::World& world, Editor* target) : core::input::ConcreteInputCommand<Editor>(world, target) {}
            void execute() const override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(core::gfx::WindowMode::Windowed);
                    getTarget()->createScene();
                }
            }
        };

        class PanLeft : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanLeft(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panHorizontal(-1.0f); }
        };

        class PanRight : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanRight(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panHorizontal(1.0f); }
        };

        class PanUp : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanUp(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panVertical(1.0f); }
        };

        class PanDown : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanDown(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panVertical(-1.0f); }
        };

        class PanIn : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanIn(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panDepth(-1.0f); }
        };

        class PanOut : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            PanOut(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->panDepth(1.0f); }
        };

        class RotateY : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            RotateY(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->rotateVertical(-getInput().value * 0.005f); }
        };

        class RotateX : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            RotateX(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->rotateHorizontal(getInput().value * 0.005f); }
        };

        class Zoom : public core::input::ConcreteInputCommand<core::gfx::CameraController> {
            public:
            Zoom(core::ecs::World& world, core::gfx::CameraController* target)
                : core::input::ConcreteInputCommand<core::gfx::CameraController>(world, target) {}
            void execute() const override { getTarget()->zoom(-getInput().value * 5.0f); }
        };
    }  // namespace editor
}  // namespace cobalt