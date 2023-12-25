//
// Created by tomas on 09-12-2023.
//

#pragma once

#include "core/gfx/mesh.h"
#include "core/gfx/camera.h"
#include "core/gfx/skybox.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        class Scene {
            public:
            /** Creates an empty scene.
             * @return: An empty scene.
             */
            Scene();
            /** Destroys the scene.
             */
            ~Scene() = default;

            /** Adds a mesh to the scene.
             * @param mesh: The mesh to add.
             * @return: The index of the mesh in the scene.
             */
            const uint addMesh(Mesh&& mesh);
            /** Removes all the meshes from the scene.
             */
            void clear();

            /** Sets the skybox of the scene.
             * @param skybox: The skybox to set.
             */
            void setSkybox(Skybox&& skybox);

            /** Gets the meshes in the scene.
             * @return: The meshes in the scene.
             */
            Vec<Mesh>& getMeshes();
            /** Gets the skybox of the scene.
             * @return: The skybox of the scene.
             */
            Opt<Skybox>& getSkybox();
            /** Gets the camera used to render the scene.
             * @return: The camera used to render the scene.
             */
            PerspectiveCamera& getCamera();

            private:
            Vec<Mesh> meshes;   // All the meshes in the scene.
                                // This is a massive oversimplification.
                                // TODO: Add a proper scene graph.
            Opt<Skybox> skybox; // The skybox of the scene.

            PerspectiveCamera camera;   // The camera used to render the scene.
        };
    }
}