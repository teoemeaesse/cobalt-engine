// Created by tomas on
// 07-12-2023

#pragma once

#include "editor/editor.h"

namespace cobalt {
    namespace editor {
        class Spawn : public engine::ConcreteInputCommand<engine::Scene> {
            public:
            Spawn(core::ecs::World& world, engine::Scene* target) : engine::ConcreteInputCommand<engine::Scene>(world, target) {}
            void execute() override {
                if (getInput().held || !getInput().active) return;
                static int i = 2;
                const engine::TextureID woodAlbedo = CB_TEXTURE_LIBRARY.getTextureID("wood-albedo");
                const engine::TextureID woodNormal = CB_TEXTURE_LIBRARY.getTextureID("wood-normal");
                const engine::TextureID woodMrao = CB_TEXTURE_LIBRARY.getTextureID("wood-mrao");
                const engine::MaterialID woodMaterial = getMaterialLibrary().makePBR("wood", woodAlbedo, woodNormal, woodMrao);
                engine::MaterialPBR& material = getMaterialLibrary().getMaterial(woodMaterial);
                engine::Mesh sphere = engine::MeshFactory::createSphere(5.0f, material);
                sphere.translate(glm::vec3(10.0f * i++, 0.0f, 0.0f));
                getTarget()->addMesh(Move(sphere));
            }
        };
        class Quit : public engine::ConcreteInputCommand<Editor> {
            public:
            Quit(core::ecs::World& world, Editor* target) : engine::ConcreteInputCommand<Editor>(world, target) {}
            void execute() override { getTarget()->stop(); }
        };

        class Fullscreen : public engine::ConcreteInputCommand<Editor> {
            public:
            Fullscreen(core::ecs::World& world, Editor* target) : engine::ConcreteInputCommand<Editor>(world, target) {}
            void execute() override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(engine::WindowMode::Fullscreen);
                    getTarget()->createScene();
                }
            }
        };

        class Borderless : public engine::ConcreteInputCommand<Editor> {
            public:
            Borderless(core::ecs::World& world, Editor* target) : engine::ConcreteInputCommand<Editor>(world, target) {}
            void execute() override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(engine::WindowMode::Borderless);
                    getTarget()->createScene();
                }
            }
        };

        class Windowed : public engine::ConcreteInputCommand<Editor> {
            public:
            Windowed(core::ecs::World& world, Editor* target) : engine::ConcreteInputCommand<Editor>(world, target) {}
            void execute() override {
                if (!getInput().active) {
                    getTarget()->getWindow().switchMode(engine::WindowMode::Windowed);
                    getTarget()->createScene();
                }
            }
        };

        class PanLeft : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanLeft(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panHorizontal(-1.0f); }
        };

        class PanRight : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanRight(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panHorizontal(1.0f); }
        };

        class PanUp : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanUp(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panVertical(1.0f); }
        };

        class PanDown : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanDown(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panVertical(-1.0f); }
        };

        class PanIn : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanIn(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panDepth(-1.0f); }
        };

        class PanOut : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            PanOut(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).panDepth(1.0f); }
        };

        class RotateY : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            RotateY(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override {
                getWorld().getResource<engine::CameraManager>().getController(*getTarget()).rotateVertical(-getInput().value * 0.005f);
            }
        };

        class RotateX : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            RotateX(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override {
                getWorld().getResource<engine::CameraManager>().getController(*getTarget()).rotateHorizontal(getInput().value * 0.005f);
            }
        };

        class Zoom : public engine::ConcreteInputCommand<engine::CameraID> {
            public:
            Zoom(core::ecs::World& world, engine::CameraID* camera) : engine::ConcreteInputCommand<engine::CameraID>(world, camera) {}
            void execute() override { getWorld().getResource<engine::CameraManager>().getController(*getTarget()).zoom(-getInput().value * 5.0f); }
        };
    }  // namespace editor
}  // namespace cobalt