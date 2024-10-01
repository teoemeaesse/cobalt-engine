// Created by tomas on
// 09-12-2023

#pragma once

#include "engine/camera/plugin.h"
#include "engine/lighting/plugin.h"
#include "engine/mesh3d/mesh.h"

namespace cobalt {
    namespace engine {
        class Scene : public core::ecs::Resource {
            public:
            /**
             * @brief Creates an empty scene.
             * @param world The ecs world.
             */
            Scene(core::ecs::World& world);
            /**
             * @brief Destroys the scene.
             */
            virtual ~Scene() noexcept = default;

            /**
             * @brief Adds a mesh to the scene.
             * @param mesh The mesh to add.
             * @return The index of the mesh in the scene.
             */
            const uint addMesh(Mesh&& mesh);
            /**
             * @brief Removes all the meshes from the scene.
             */
            void clear();

            /**
             * @brief Sets the skybox of the scene.
             * @param skybox The skybox to use.
             */
            void setSkybox(Mesh&& skybox);

            /**
             * @brief Gets the meshes in the scene.
             * @return The meshes in the scene.
             */
            Vec<Mesh>& getMeshes();
            /**
             * @brief Gets the skybox of the scene.
             * @return The skybox of the scene.
             */
            Opt<Mesh>& getSkybox();
            /**
             * @brief Gets the ID for the camera used to render the scene.
             * @return CameraID
             */
            CameraID& getCameraID();

            private:           // TODO: Add a proper scene graph.
            Vec<Mesh> meshes;  ///< All the meshes in the scene.
            Opt<Mesh> skybox;  ///< The skybox of the scene.
            CameraID camera;   ///< The ID for the camera used to render the scene.
        };
    }  // namespace engine
}  // namespace cobalt