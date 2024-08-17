// Created by tomas on
// 09-12-2023

#include "engine/scene/scene.h"

#include "core/ecs/world.h"
#include "engine/camera/controller.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Scene::Scene(core::ecs::World& world)
            : camera(world.getResource<CameraManager>().addCamera<PivotCamera>("scene_camera", CameraProperties()
                                                                                                   .setPosition(glm::vec3(-45.0, 15.0, 5.0))
                                                                                                   .setDirection(glm::vec2(180.0, 70.0))
                                                                                                   .setDistance(50.0f)
                                                                                                   .setFOV(90.0f)
                                                                                                   .setClippingPlanes(0.01f, 1000.0f)
                                                                                                   .setAspectRatio(16.0f / 9.0f)
                                                                                                   .setLinearCling(0.3f)
                                                                                                   .setAngularCling(0.8f)
                                                                                                   .setZoomCling(0.4f))) {}

        const uint Scene::addMesh(Mesh&& mesh) {
            meshes.push_back(Move(mesh));
            return meshes.size() - 1;
        }

        void Scene::clear() {
            meshes.clear();
            this->skybox.reset();
        }

        void Scene::setSkybox(Mesh&& skybox) { this->skybox.emplace(Move(skybox)); }

        Vec<Mesh>& Scene::getMeshes() { return meshes; }

        Opt<Mesh>& Scene::getSkybox() { return skybox; }

        CameraID& Scene::getCameraID() { return camera; }
    }  // namespace engine
}  // namespace cobalt