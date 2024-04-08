// Created by tomas on
// 02-04-2024

#pragma once

#include "core/ecs/resource/resource.h"
#include "engine/camera/controller.h"

namespace cobalt {
    namespace engine {
        class CameraManager : public core::ecs::Resource {
            public:
            /**
             * @brief: Create a camera manager.
             * @return: The camera manager.
             */
            CameraManager() = default;
            /**
             * @brief: Destroy the camera manager.
             * @return: void
             */
            ~CameraManager() = default;

            /**
             * @brief: Add a camera with the given name and properties.
             * @param name: Name of the camera.
             * @param properties: Properties of the camera.
             * @return: The ID of the camera.
             */
            template <typename T>
            CameraID addCamera(const std::string& name, const CameraProperties& properties) {
                if (cameraNames.contains(name)) {
                    CB_CORE_ERROR("Camera with name {0} already exists", name);
                }
                const CameraID id = cameras.size();
                cameraNames[name] = id;
                cameras.erase(id);
                cameras.emplace(id, CameraController::create<T>(properties));
                return id;
            }

            /**
             * @brief: Get the camera with the given ID.
             * @param id: ID of the camera.
             * @return: The camera's controller.
             */
            CameraController& getController(const CameraID id);
            /**
             * @brief: Get the camera with the given ID.
             * @param id: ID of the camera.
             * @return: The camera's controller.
             */
            const CameraController& getController(const CameraID id) const;
            /**
             * @brief: Get the camera with the given name.
             * @param name: Name of the camera.
             * @return: The camera's controller.
             */
            CameraController& getController(const std::string& name);
            /**
             * @brief: Get the camera with the given name.
             * @param name: Name of the camera.
             * @return: The camera's controller.
             */
            const CameraController& getController(const std::string& name) const;

            private:
            UMap<std::string, CameraID> cameraNames;
            UMap<CameraID, CameraController> cameras;
        };
    }  // namespace engine
}  // namespace cobalt