// Created by tomas on
// 09-12-2023

#pragma once

#include "core/ecs/resource/resource.h"
#include "engine/camera/plugin.h"
#include "engine/renderer3d/mesh.h"
#include "engine/renderer3d/skybox.h"

namespace cobalt {
    namespace engine {
        class Scene : public core::ecs::Resource {
            public:
            /**
             * @brief: Creates an empty scene.
             * @return: An empty scene.
             */
            Scene();
            /**
             * @brief: Destroys the scene.
             */
            ~Scene() = default;

            /**
             * @brief: Adds a mesh to the scene.
             * @param mesh: The mesh to add.
             * @return: The index of the mesh in the scene.
             */
            const uint addMesh(Mesh&& mesh);
            /**
             * @brief: Removes all the meshes from the scene.
             * @return: void
             */
            void clear();

            /**
             * @brief: Sets the skybox of the scene.
             * @param skybox: The skybox to set.
             * @return: void
             */
            void setSkybox(Skybox&& skybox);

            /**
             * @brief: Gets the meshes in the scene.
             * @return: The meshes in the scene.
             */
            Vec<Mesh>& getMeshes();
            /**
             * @brief: Gets the skybox of the scene.
             * @return: The skybox of the scene.
             */
            Opt<Skybox>& getSkybox();
            /**
             * @brief: Gets the camera controller used to render the scene.
             * @return: The camera controller used to render the scene.
             */
            CameraController& getCameraController();

            private:
            Vec<Mesh> meshes;    // All the meshes in the scene.
                                 // This is a massive oversimplification.
                                 // TODO: Add a proper scene graph.
            Opt<Skybox> skybox;  // The skybox of the scene.

            CameraController camera;  // The camera used to render the scene.
        };
    }  // namespace engine
}  // namespace cobalt