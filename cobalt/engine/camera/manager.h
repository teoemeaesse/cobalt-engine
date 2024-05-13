// Created by tomas on
// 02-04-2024

#pragma once

#include "core/ecs/resource/resource.h"
#include "engine/camera/controller.h"

namespace cobalt {
    namespace engine {
        class CameraID {
            friend class CameraManager;

            public:
            /**
             * @brief Create a camera ID with the given handle and name.
             * @param handle The handle of the camera.
             * @param name The name of the camera.
             * @param owner The camera manager that owns the camera.
             */
            CameraID(const uint handle, const std::string& name, CameraManager& owner) noexcept;
            /**
             * @brief Default destructor.
             */
            ~CameraID() noexcept = default;
            /**
             * @brief Default copy constructor.
             */
            CameraID(const CameraID& other) noexcept;
            /**
             * @brief Default move constructor.
             */
            CameraID(CameraID&& other) noexcept;
            /**
             * @brief Default copy assignment operator.
             */
            CameraID& operator=(const CameraID& other) noexcept;
            /**
             * @brief Default move assignment operator.
             */
            CameraID& operator=(CameraID&& other) noexcept;

            /**
             * @brief Check if two camera IDs are equal.
             * @param other The other camera ID.
             * @return True if the handles are equal, false otherwise.
             */
            bool operator==(const CameraID& other) const;

            /**
             * @brief Get the handle of the camera.
             * @return The handle of the camera.
             */
            const uint getHandle() const;
            /**
             * @brief Get the name of the camera.
             * @return The name of the camera.
             */
            const std::string& getName() const;
            /**
             * @brief Get the camera controller.
             * @return The camera controller.
             */
            CameraController& getController();
            /**
             * @brief Get the camera.
             * @return The camera.
             */
            Camera& getCamera();

            private:
            uint handle;
            std::string name;
            CameraManager& owner;
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::engine::CameraID> {
        size_t operator()(const cobalt::engine::CameraID& id) const { return hash<uint>()(id.getHandle()); }
    };
}  // namespace std

namespace cobalt {
    namespace engine {

        class CameraManager : public core::ecs::Resource {
            public:
            /**
             * @brief Default constructor.
             */
            CameraManager() = default;
            /**
             * @brief Default destructor.
             */
            ~CameraManager() = default;

            /**
             * @brief Add a camera with the given name and properties.
             * @param name Name of the camera.
             * @param properties Properties of the camera.
             * @return The ID of the camera.
             */
            template <typename T>
            CameraID& addCamera(const std::string& name, const CameraProperties& properties) {
                static_assert(std::is_base_of<Camera, T>::value, "T must be a Camera type.");
                if (cameraNames.contains(name)) {
                    CB_CORE_ERROR("Camera with name {0} already exists", name);
                }
                CameraID id(cameras.size(), name, *this);
                cameraNames.emplace(name, id);
                cameras.erase(id);
                cameras.emplace(id, CameraController::create<T>(properties));
                return cameraNames.at(name);
            }

            /**
             * @brief Get the camera controller with the given ID.
             * @param id ID of the camera.
             * @return The camera's controller.
             */
            CameraController& getController(const CameraID& id);
            /**
             * @brief Get the camera controller with the given ID.
             * @param id ID of the camera.
             * @return The camera's controller.
             */
            const CameraController& getController(const CameraID& id) const;
            /**
             * @brief Get the camera controller with the given name.
             * @param name Name of the camera.
             * @return The camera's controller.
             */
            CameraController& getController(const std::string& name);
            /**
             * @brief Get the camera controller with the given name.
             * @param name Name of the camera.
             * @return The camera's controller.
             */
            const CameraController& getController(const std::string& name) const;

            /**
             * @brief Get the camera with the given ID.
             * @param id ID of the camera.
             * @return The camera.
             */
            Camera& getCamera(const CameraID& id);
            /**
             * @brief Get the camera with the given ID.
             * @param id ID of the camera.
             * @return The camera.
             */
            const Camera& getCamera(const CameraID& id) const;
            /**
             * @brief Get the camera with the given name.
             * @param name Name of the camera.
             * @return The camera.
             */
            Camera& getCamera(const std::string& name);
            /**
             * @brief Get the camera with the given name.
             * @param name Name of the camera.
             * @return The camera.
             */
            const Camera& getCamera(const std::string& name) const;

            private:
            UMap<std::string, CameraID> cameraNames;
            UMap<CameraID, CameraController> cameras;
        };
    }  // namespace engine
}  // namespace cobalt