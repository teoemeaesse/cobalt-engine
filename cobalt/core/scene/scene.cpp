//
// Created by tomas on 09-12-2023.
//

#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        Scene::Scene() :
            camera(CameraController::create<PivotCamera>(
                core::CameraProperties().
                    setPosition(glm::vec3(-45.0, 15.0, 5.0)).
                    setDirection(glm::vec2(180.0, 70.0)).
                    setDistance(50.0f).
                    setFOV(90.0f).
                    setClippingPlanes(5.0f, 1000.0f).
                    setAspectRatio(16.0f / 9.0f).
                    setLinearCling(0.3f).
                    setAngularCling(0.8f).
                    setZoomCling(0.4f)
            ))
        {}

        const uint Scene::addMesh(Mesh&& mesh) {
            meshes.push_back(std::move(mesh));
            return meshes.size() - 1;
        }

        void Scene::clear() {
            meshes.clear();
            this->skybox.reset();
        }

        void Scene::setSkybox(Skybox&& skybox) {
            this->skybox.emplace(std::move(skybox));
        }

        Vec<Mesh>& Scene::getMeshes() {
            return meshes;
        }

        Opt<Skybox>& Scene::getSkybox() {
            return skybox;
        }

        CameraController& Scene::getCameraController() {
            return camera;
        }
    }
}