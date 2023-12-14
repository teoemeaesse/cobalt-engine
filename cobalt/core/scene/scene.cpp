//
// Created by tomas on 09-12-2023.
//

#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        Scene::Scene() :
            meshes(8),
            camera(glm::vec3(0.0, 0.0, 10.0),
                   glm::vec2(90.0, 90.0),
                   120.0f, 25.0f,
                   1.0f, 1000.0f,
                   16.0f / 9.0f)
        {}

        const uint Scene::addMesh(Mesh&& mesh) {
            meshes.push(std::move(mesh));
            return meshes.getSize() - 1;
        }

        Vector<Mesh>& Scene::getMeshes() {
            return meshes;
        }

        PerspectiveCamera& Scene::getCamera() {
            return camera;
        }
    }
}