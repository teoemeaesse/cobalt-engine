//
// Created by tomas on 09-12-2023.
//

#pragma once

#include "core/containers/vector.h"
#include "core/gfx/mesh.h"


namespace cobalt {
    namespace core {
        class Scene {
            public:
            /* Creates an empty scene.
             * @return: An empty scene.
             */
            Scene();
            /* Destroys the scene.
             */
            ~Scene() = default;

            /* Adds a mesh to the scene.
             * @param mesh: The mesh to add.
             * @return: The index of the mesh in the scene.
             */
            const uint addMesh(std::unique_ptr<Mesh> mesh);

            private:
            Vector<std::unique_ptr<Mesh>> meshes;   // All the meshes in the scene.
                                                    // This is a massive oversimplification.
                                                    // TODO: Add a proper scene graph.
        };
    }
}