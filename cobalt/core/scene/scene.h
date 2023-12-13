//
// Created by tomas on 09-12-2023.
//

#pragma once

#include "core/containers/vector.h"
#include "core/gfx/mesh.h"
#include "core/gfx/camera.h"


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
            const uint addMesh(Mesh&& mesh);

            /* Gets the meshes in the scene.
             * @return: The meshes in the scene.
             */
            Vector<Mesh>& getMeshes();

            /* Gets the camera used to render the scene.
             * @return: The camera used to render the scene.
             */
            PerspectiveCamera& getCamera();

            private:
            Vector<Mesh> meshes;    // All the meshes in the scene.
                                    // This is a massive oversimplification.
                                    // TODO: Add a proper scene graph.
            
            PerspectiveCamera camera;   // The camera used to render the scene.
        };
    }
}