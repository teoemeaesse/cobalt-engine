// Created by tomas on
// 09-12-2023

#include "core/scene/scene.h"

namespace cobalt {
    namespace core::scene {
        Scene::Scene()
            : camera(gfx::CameraController::create<gfx::PivotCamera>(gfx::CameraProperties()
                                                                         .setPosition(glm::vec3(-45.0, 15.0, 5.0))
                                                                         .setDirection(glm::vec2(180.0, 70.0))
                                                                         .setDistance(50.0f)
                                                                         .setFOV(90.0f)
                                                                         .setClippingPlanes(5.0f, 1000.0f)
                                                                         .setAspectRatio(16.0f / 9.0f)
                                                                         .setLinearCling(0.3f)
                                                                         .setAngularCling(0.8f)
                                                                         .setZoomCling(0.4f))) {}

        const uint Scene::addMesh(gfx::Mesh&& mesh) {
            meshes.push_back(Move(mesh));
            return meshes.size() - 1;
        }

        void Scene::clear() {
            meshes.clear();
            this->skybox.reset();
        }

        void Scene::setSkybox(gfx::Skybox&& skybox) { this->skybox.emplace(Move(skybox)); }

        Vec<gfx::Mesh>& Scene::getMeshes() { return meshes; }

        Opt<gfx::Skybox>& Scene::getSkybox() { return skybox; }

        gfx::CameraController& Scene::getCameraController() { return camera; }
    }  // namespace core::scene
}  // namespace cobalt