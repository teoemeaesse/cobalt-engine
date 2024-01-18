//
// Created
// by
// tomas
// on
// 09-12-2023.
//

#pragma once

#include "core/gfx/camera_controller.h"
#include "core/gfx/mesh.h"
#include "core/gfx/skybox.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::scene {
        class Scene {
            public:
            /** @brief: Creates an empty scene.
             * @return: An empty scene.
             */
            Scene();
            /** @brief: Destroys the scene.
             */
            ~Scene() = default;

            /** @brief: Adds a mesh to the scene.
             * @param mesh: The mesh to add.
             * @return: The index of the mesh in the scene.
             */
            const uint addMesh(gfx::Mesh&& mesh);
            /** @brief: Removes all the meshes from the scene.
             */
            void clear();

            /** @brief: Sets the skybox of the scene.
             * @param skybox: The skybox to set.
             */
            void setSkybox(gfx::Skybox&& skybox);

            /** @brief: Gets the meshes in the scene.
             * @return: The meshes in the scene.
             */
            Vec<gfx::Mesh>& getMeshes();
            /** @brief: Gets the skybox of the scene.
             * @return: The skybox of the scene.
             */
            Opt<gfx::Skybox>& getSkybox();
            /** @brief: Gets the camera controller used to render the scene.
             * @return: The camera controller used to render the scene.
             */
            gfx::CameraController& getCameraController();

            private:
            Vec<gfx::Mesh> meshes;    // All the meshes in the scene.
                                      // This is a massive oversimplification.
                                      // TODO: Add a proper scene graph.
            Opt<gfx::Skybox> skybox;  // The skybox of the scene.

            gfx::CameraController camera;  // The camera used to render the scene.
        };
    }  // namespace core::scene
}  // namespace cobalt