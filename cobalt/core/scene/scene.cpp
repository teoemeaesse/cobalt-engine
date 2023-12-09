//
// Created by tomas on 09-12-2023.
//

#include "core/scene/scene.h"


namespace cobalt {
    namespace core {
        Scene::Scene() : meshes(1) {
        }

        const uint Scene::addMesh(std::unique_ptr<Mesh> mesh) {
            meshes.push(std::move(mesh));
            return meshes.getSize() - 1;
        }
    }
}