//
// Created by tomas on 09-12-2023.
//

#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        Scene::Scene() :
            camera(glm::vec3(-45.0, 15.0, 5.0),
                   glm::vec2(180.0, 70.0),
                   50.0f,
                   90.0f, 25.0f,
                   5.0f, 1000.0f,
                   16.0f / 9.0f)
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

        PerspectiveCamera& Scene::getCamera() {
            return camera;
        }
    }
}