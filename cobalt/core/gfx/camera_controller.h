//
// Created by tomas on 28-12-2023.
//

#pragma once

#include "core/gfx/camera.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        using CameraID = uint;

        class CameraProperties {
            public:
            enum class Type {
                Static,
                // Follow,
                Free
            };
            /** Create a camera properties object with default values.
             * @return: The camera properties.
             */
            CameraProperties();
            /** Destroy the camera properties object.
             */
            ~CameraProperties() = default;

            /** Create a camera from the properties.
             * @return: The camera.
             */
            template<typename T>
            T getCamera() const;

            /** Set the type of camera movement.
             * Static: The camera stays in the same position. Shorthand for setting cling to 0.
             * Follow: The camera follows a target.
             * Free: The camera can be moved freely.
             * @param type: Type of camera movement.
             * @return: Reference to this object.
             */
            CameraProperties& setType(const Type type);
            /** Set the initial position of the camera.
             * @param position: Position of the camera.
             * @return: Reference to this object.
             */
            CameraProperties& setPosition(const glm::vec3& position);
            /** Set the initial center position of the camera.
             * Only applicable to pivot mode. Overrides the direction.
             * @param center: Center position of the camera.
             * @return: Reference to this object.
             */
            CameraProperties& setCenter(const glm::vec3& center);
            /** Set the initial direction of the camera.
             * @param direction: Direction of the camera (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180 looking right (+x)
             *                   y: 0 looking down (-y), 90 looking forward (-z), 180 looking up (+y)
             * @return: Reference to this object.
             */
            CameraProperties& setDirection(const glm::vec2& direction);
            /** Set how much the camera sticks to the target position.
             * 0 is static, 1 is fully attached.
             * @param cling: Cling value.
             * @return: Reference to this object.
             */
            CameraProperties& setCling(const float cling);
            /** Set how fast the camera moves.
             * @param linearVelocity: Linear velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setLinearVelocity(const float linearVelocity);
            /** Set how fast the camera rotates.
             * @param angularVelocity: Angular velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setAngularVelocity(const float angularVelocity);
            /** Set how fast the camera zooms.
             * @param zoomVelocity: Zoom velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setZoomVelocity(const float zoomVelocity);
            /** Set the field of view (degrees).
             * @param fov: Field of view.
             * @return: Reference to this object.
             */
            CameraProperties& setFOV(const float fov);
            /** Set the aspect ratio. Only applicable to perspective modes.
             * @param aspectRatio: Aspect ratio.
             * @return: Reference to this object.
             */
            CameraProperties& setAspectRatio(const float aspectRatio);
            /** Set the distance from the camera to the center position.
             * Only applicable to pivot mode.
             * @param distance: Distance.
             * @return: Reference to this object.
             */
            CameraProperties& setDistance(const float distance);
            /** Set the near and far clipping planes.
             * @param near: Near plane.
             * @param far: Far plane.
             * @return: Reference to this object.
             */
            CameraProperties& setClippingPlanes(const float near, const float far);
            /** Set the left, right, top and bottom planes.
             * Only applicable to orthographic mode.
             * @param left: Left plane.
             * @param right: Right plane.
             * @param top: Top plane.
             * @param bottom: Bottom plane.
             * @return: Reference to this object.
             */
            CameraProperties& setOrthoPlanes(const float left, const float right, const float top, const float bottom);

            /** Get the type of camera movement.
             * @return: Type of camera movement.
             */
            const Type getType() const;
            /** Get the initial position of the camera.
             * @return: Position of the camera.
             */
            const glm::vec3& getPosition() const;
            /** Get the initial center position of the camera.
             * Only applicable to pivot mode.
             * @return: Center position of the camera.
             */
            const glm::vec3& getCenter();
            /** Get the initial direction of the camera.
             * @return: Direction of the camera (degrees).
             */
            const glm::vec2& getDirection() const;
            /** Get how much the camera sticks to the target position.
             * @return: Cling value.
             */
            const float getCling() const;
            /** Get how fast the camera moves.
             * @return: Linear velocity.
             */
            const float getLinearVelocity() const;
            /** Get how fast the camera rotates.
             * @return: Angular velocity.
             */
            const float getAngularVelocity() const;
            /** Get how fast the camera zooms.
             * @return: Zoom velocity.
             */
            const float getZoomVelocity() const;
            /** Get the field of view (degrees).
             * @return: Field of view.
             */
            const float getFOV() const;
            /** Get the aspect ratio.
             * @return: Aspect ratio.
             */
            const float getAspectRatio() const;
            /** Get the distance from the camera to the center position.
             * Only applicable to pivot mode.
             * @return: Distance.
             */
            const float getDistance() const;
            /** Get the near clipping plane.
             * @return: Near plane.
             */
            const float getNear() const;
            /** Get the far clipping plane.
             * @return: Far plane.
             */
            const float getFar() const;
            /** Get the left clipping plane.
             * Only applicable to orthographic mode.
             * @return: Left clipping plane.
             */
            const float getLeft() const;
            /** Get the right clipping plane.
             * Only applicable to orthographic mode.
             * @return: Right clipping plane.
             */
            const float getRight() const;
            /** Get the top clipping plane.
             * Only applicable to orthographic mode.
             * @return: Top clipping plane.
             */
            const float getTop() const;
            /** Get the bottom clipping plane.
             * Only applicable to orthographic mode.
             * @return: Bottom clipping plane.
             */
            const float getBottom() const;

            private:
            Type type;              // Type of camera movement.
            glm::vec3 position;     // Position of the camera.
            Opt<glm::vec3> center;  // Center position of the camera (for pivot mode).
            glm::vec2 direction;    // Direction of the camera.
            float cling;            // How much the camera sticks to the target position.
            float linearVelocity;   // How fast the camera moves.
            float angularVelocity;  // How fast the camera rotates.
            float zoomVelocity;     // How fast the camera zooms.
            float fov;              // Field of view.
            float aspectRatio;      // Aspect ratio.
            float distance;         // Distance from the camera to the center position.
            float near, far;        // Near and far planes.
            float left, right;      // Left and right planes (for orthographic mode).
            float top, bottom;      // Top and bottom planes (for orthographic mode).
        };

        class CameraController {
            public:
            /** Create a camera controller from the given properties.
             * @param properties: The camera properties.
             * @return: The camera controller.
             */
            template<typename T>
            CameraController(const CameraProperties& properties) : camera(std::move(createScope(properties.getCamera<T>()))) {}
            /** Destroy the camera controller.
             */
            ~CameraController() = default;

            /** Resizes the camera.
             * @param left: The left plane of the viewport.
             * @param right: The right plane of the viewport.
             * @param bottom: The bottom plane of the viewport.
             * @param top: The top plane of the viewport.
             */
            void resize(const float left, const float right, const float bottom, const float top);
            /** Resizes the camera.
             * @param aspectRatio: The aspect ratio of the viewport.
             */
            void resize(const float aspectRatio);
            /** Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount);
            /** Rotates the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount);
            /** Rotates the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount);
            /** Pans the camera by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount);
            /** Pans the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount);
            /** Pans the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount);

            private:
            Scope<Camera> camera;
            glm::vec3 targetPosition;
        };

        class CameraManager {
            public:
            /** Create a camera manager.
             * @return: The camera manager.
             */
            CameraManager() = default;
            /** Destroy the camera manager.
             */
            ~CameraManager() = default;

            /** Add a camera with the given name and properties.
             * @param name: Name of the camera.
             * @param properties: Properties of the camera.
             * @return: The ID of the camera.
             */
            template<typename T>
            CameraID addCamera(const std::string& name, const CameraProperties& properties) {
                if (cameraNames.contains(name)) {
                    CB_CORE_ERROR("Camera with name {0} already exists", name);
                }
                const CameraID id = cameras.size();
                cameraNames[name] = id;
                cameras[id] = CameraController(properties);
                return id;
            }
            
            /** Get the camera with the given ID.
             * @param id: ID of the camera.
             * @return: The camera.
             */
            CameraController& getCamera(const CameraID id);
            /** Get the camera with the given name.
             * @param name: Name of the camera.
             * @return: The camera.
             */
            CameraController& getCamera(const std::string& name);

            private:
            UMap<std::string, CameraID> cameraNames;
            UMap<CameraID, CameraController> cameras;
        };
    }
}

template<typename T>
T cobalt::core::CameraProperties::getCamera() const {
    CB_CORE_ERROR("Invalid camera mode");
}
/** Create an orthographic camera from the properties.
 * @return: The camera.
 */
template<>
cobalt::core::OrthographicCamera cobalt::core::CameraProperties::getCamera<cobalt::core::OrthographicCamera>() const {
    return OrthographicCamera(position, direction, left, right, top, bottom, near, far);
}
/** Create a first person perspective camera from the properties.
 * @return: The camera.
 */
template<>
cobalt::core::FPSCamera cobalt::core::CameraProperties::getCamera<cobalt::core::FPSCamera>() const {
    return cobalt::core::FPSCamera(position, direction, fov, near, far, aspectRatio);
}
/** Create a pivot camera from the properties.
 * @return: The camera.
 */
template<>
cobalt::core::PivotCamera cobalt::core::CameraProperties::getCamera<cobalt::core::PivotCamera>() const {
    if (center.has_value()) {
        return cobalt::core::PivotCamera(position, center.value(), fov, near, far, aspectRatio);
    } else {
        return cobalt::core::PivotCamera(position, direction, distance, fov, near, far, aspectRatio);
    }
}