// Created by tomas on
// 28-12-2023

#pragma once

#include "core/gfx/camera.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
        using CameraID = uint;

        class CameraProperties {
            public:
            enum class Type {
                Static,
                // Follow,
                Free
            };
            /** @brief: Create a camera properties object with default values.
             * @return: The camera properties.
             */
            CameraProperties();
            /** @brief: Destroy the camera properties object.
             */
            ~CameraProperties() = default;

            /** @brief: Create a camera from the properties.
             * @return: The camera.
             */
            template <typename T>
            T getCamera() const;

            /** @brief: Set the type of camera movement.
             * Static: The camera stays in the same position. Shorthand for setting cling
             * to 0. Follow: The camera follows a target. Free: The camera can be moved
             * freely.
             * @param type: Type of camera movement.
             * @return: Reference to this object.
             */
            CameraProperties& setType(const Type type);
            /** @brief: Set the initial position of the camera.
             * @param position: Position of the camera.
             * @return: Reference to this object.
             */
            CameraProperties& setPosition(const glm::vec3& position);
            /** @brief: Set the initial center position of the camera.
             * Only applicable to pivot mode. Overrides the direction.
             * @param center: Center position of the camera.
             * @return: Reference to this object.
             */
            CameraProperties& setCenter(const glm::vec3& center);
            /** @brief: Set the initial direction of the camera.
             * @param direction: Direction of the camera (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180
             * looking right (+x) y: 0 looking down (-y), 90 looking forward (-z), 180
             * looking up (+y)
             * @return: Reference to this object.
             */
            CameraProperties& setDirection(const glm::vec2& direction);
            /** @brief: Set how fast the camera reacts to a change in position.
             * 0 is static, 1 is fully attached.
             * @param linearCling: Cling value.
             * @return: Reference to this object.
             */
            CameraProperties& setLinearCling(const float linearCling);
            /** @brief: Set how fast the camera moves.
             * @param linearVelocity: Linear velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setLinearVelocity(const float linearVelocity);
            /** @brief: Set how fast the camera reacts to a change in direction.
             * 0 is static, 1 is fully attached.
             * @param angularCling: Cling value.
             * @return: Reference to this object.
             */
            CameraProperties& setAngularCling(const float angularCling);
            /** @brief: Set how fast the camera rotates.
             * @param angularVelocity: Angular velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setAngularVelocity(const float angularVelocity);
            /** @brief: Set how fast the camera reacts to a change in zoom.
             * 0 is static, 1 is fully attached.
             * @param zoomCling: Cling value.
             * @return: Reference to this object.
             */
            CameraProperties& setZoomCling(const float zoomCling);
            /** @brief: Set how fast the camera zooms.
             * @param zoomVelocity: Zoom velocity.
             * @return: Reference to this object.
             */
            CameraProperties& setZoomVelocity(const float zoomVelocity);
            /** @brief: Set the field of view (degrees).
             * @param fov: Field of view.
             * @return: Reference to this object.
             */
            CameraProperties& setFOV(const float fov);
            /** @brief: Set the aspect ratio. Only applicable to perspective modes.
             * @param aspectRatio: Aspect ratio.
             * @return: Reference to this object.
             */
            CameraProperties& setAspectRatio(const float aspectRatio);
            /** @brief: Set the distance from the camera to the center position.
             * Only applicable to pivot mode.
             * @param distance: Distance.
             * @return: Reference to this object.
             */
            CameraProperties& setDistance(const float distance);
            /** @brief: Set the near and far clipping planes.
             * @param near: Near plane.
             * @param far: Far plane.
             * @return: Reference to this object.
             */
            CameraProperties& setClippingPlanes(const float near, const float far);
            /** @brief: Set the left, right, top and bottom planes.
             * Only applicable to orthographic mode.
             * @param left: Left plane.
             * @param right: Right plane.
             * @param top: Top plane.
             * @param bottom: Bottom plane.
             * @return: Reference to this object.
             */
            CameraProperties& setOrthoPlanes(const float left, const float right, const float top, const float bottom);

            /** @brief: Get the type of camera movement.
             * @return: Type of camera movement.
             */
            const Type getType() const;
            /** @brief: Get the initial position of the camera.
             * @return: Position of the camera.
             */
            const glm::vec3& getPosition() const;
            /** @brief: Get the initial center position of the camera.
             * Only applicable to pivot mode.
             * @return: Center position of the camera.
             */
            const glm::vec3& getCenter();
            /** @brief: Get the initial direction of the camera.
             * @return: Direction of the camera (degrees).
             */
            const glm::vec2& getDirection() const;
            /** @brief: Get how fast the camera reacts to a change in position.
             * @return: Cling value.
             */
            const float getLinearCling() const;
            /** @brief: Get how fast the camera moves.
             * @return: Linear velocity.
             */
            const float getLinearVelocity() const;
            /** @brief: Get how fast the camera reacts to a change in direction.
             * @return: Cling value.
             */
            const float getAngularCling() const;
            /** @brief: Get how fast the camera rotates.
             * @return: Angular velocity.
             */
            const float getAngularVelocity() const;
            /** @brief: Get how fast the camera reacts to a change in zoom.
             * @return: Cling value.
             */
            const float getZoomCling() const;
            /** @brief: Get how fast the camera zooms.
             * @return: Zoom velocity.
             */
            const float getZoomVelocity() const;
            /** @brief: Get the field of view (degrees).
             * @return: Field of view.
             */
            const float getFOV() const;
            /** @brief: Get the aspect ratio.
             * @return: Aspect ratio.
             */
            const float getAspectRatio() const;
            /** @brief: Get the distance from the camera to the center position.
             * Only applicable to pivot mode.
             * @return: Distance.
             */
            const float getDistance() const;
            /** @brief: Get the near clipping plane.
             * @return: Near plane.
             */
            const float getNear() const;
            /** @brief: Get the far clipping plane.
             * @return: Far plane.
             */
            const float getFar() const;
            /** @brief: Get the left clipping plane.
             * Only applicable to orthographic mode.
             * @return: Left clipping plane.
             */
            const float getLeft() const;
            /** @brief: Get the right clipping plane.
             * Only applicable to orthographic mode.
             * @return: Right clipping plane.
             */
            const float getRight() const;
            /** @brief: Get the top clipping plane.
             * Only applicable to orthographic mode.
             * @return: Top clipping plane.
             */
            const float getTop() const;
            /** @brief: Get the bottom clipping plane.
             * Only applicable to orthographic mode.
             * @return: Bottom clipping plane.
             */
            const float getBottom() const;

            private:
            Type type;              // Type of camera movement.
            glm::vec3 position;     // Position of the camera.
            Opt<glm::vec3> center;  // Center position of the camera (for pivot mode).
            glm::vec2 direction;    // Direction of the camera.
            float linearCling;      // How fast the camera reacts to a change in position.
            float linearVelocity;   // How fast the camera moves.
            float angularCling;     // How much the camera reacts to a change in direction.
            float angularVelocity;  // How fast the camera rotates.
            float zoomCling;        // How much the camera reacts to a change in zoom.
            float zoomVelocity;     // How fast the camera zooms.
            float fov;              // Field of view.
            float aspectRatio;      // Aspect ratio.
            float distance;         // Distance from the camera to the center position.
            float near,
                far;  // Near and far planes.
            float left,
                right;  // Left and right planes (for orthographic mode).
            float top,
                bottom;  // Top and bottom planes (for orthographic mode).
        };

        class CameraController {
            public:
            /** @brief: Destroy the camera controller.
             */
            ~CameraController() = default;

            /** @brief: Create a camera controller from the given properties.
             * @param properties: Properties of the camera.
             * @return: The camera controller.
             */
            template <typename T>
            static CameraController create(const CameraProperties& properties);

            /** @brief: Get the camera.
             * @return: The camera.
             */
            Camera& getCamera() const;

            /** @brief: Update the camera.
             */
            void update();

            /** @brief: Resizes the camera.
             * @param left: The left plane of the viewport.
             * @param right: The right plane of the viewport.
             * @param bottom: The bottom plane of the viewport.
             * @param top: The top plane of the viewport.
             */
            void resize(const float left, const float right, const float bottom, const float top);
            /** @brief: Resizes the camera.
             * @param aspectRatio: The aspect ratio of the viewport.
             */
            void resize(const float aspectRatio);
            /** @brief: Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount);
            /** @brief: Rotates the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount);
            /** @brief: Rotates the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount);
            /** @brief: Pans the camera by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount);
            /** @brief: Pans the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount);
            /** @brief: Pans the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount);

            private:
            Scope<Camera> camera;

            glm::vec3 deltaLinear;
            glm::vec2 deltaAngular;
            float deltaZoom;

            const float linearCling;
            const float angularCling;
            const float zoomCling;

            /** @brief: Create a camera controller for the given camera.
             * @param camera: The camera to control.
             * @param linearCling: How fast the camera reacts to a change in position.
             * @param angularCling: How much the camera reacts to a change in direction.
             * @param zoomCling: How much the camera reacts to a change in zoom.
             * @return: The camera controller.
             */
            CameraController(Scope<Camera> camera, float linearCling, float angularCling, float zoomCling);
        };

        class CameraManager {
            public:
            /** @brief: Create a camera manager.
             * @return: The camera manager.
             */
            CameraManager() = default;
            /** @brief: Destroy the camera manager.
             */
            ~CameraManager() = default;

            /** @brief: Add a camera with the given name and properties.
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
                cameras[id](std::move(createScope(properties.getCamera<T>())));
                return id;
            }

            /** @brief: Get the camera with the given ID.
             * @param id: ID of the camera.
             * @return: The camera.
             */
            CameraController& getCamera(const CameraID id);
            /** @brief: Get the camera with the given name.
             * @param name: Name of the camera.
             * @return: The camera.
             */
            CameraController& getCamera(const std::string& name);

            private:
            UMap<std::string, CameraID> cameraNames;
            UMap<CameraID, CameraController> cameras;
        };
    }  // namespace core::gfx
}  // namespace cobalt

template <typename T>
T inline cobalt::core::gfx::CameraProperties::getCamera() const {
    static_assert(std::is_base_of<Camera, T>::value, "T must be a camera type");
    throw GFXException("Invalid camera mode");
}
/** @brief: Create an orthographic camera from the properties.
 * @return: The camera.
 */
template <>
cobalt::core::gfx::OrthographicCamera inline cobalt::core::gfx::CameraProperties::getCamera<cobalt::core::gfx::OrthographicCamera>() const {
    return OrthographicCamera(position, direction, left, right, top, bottom, near, far);
}
/** @brief: Create a first person perspective camera from the properties.
 * @return: The camera.
 */
template <>
cobalt::core::gfx::FPSCamera inline cobalt::core::gfx::CameraProperties::getCamera<cobalt::core::gfx::FPSCamera>() const {
    return cobalt::core::gfx::FPSCamera(position, direction, fov, near, far, aspectRatio);
}
/** @brief: Create a pivot camera from the properties.
 * @return: The camera.
 */
template <>
cobalt::core::gfx::PivotCamera inline cobalt::core::gfx::CameraProperties::getCamera<cobalt::core::gfx::PivotCamera>() const {
    if (center.has_value()) {
        return cobalt::core::gfx::PivotCamera(position, center.value(), fov, near, far, aspectRatio);
    } else {
        return cobalt::core::gfx::PivotCamera(position, direction, distance, fov, near, far, aspectRatio);
    }
}
template <typename T>
cobalt::core::gfx::CameraController inline cobalt::core::gfx::CameraController::create(const cobalt::core::gfx::CameraProperties& properties) {
    static_assert(std::is_base_of<Camera, T>::value, "T must be a camera type");
    throw GFXException("Invalid camera mode");
}
/** @brief: Create an orthographic camera controller from the given properties.
 * @param properties: Properties of the camera.
 * @return: The camera controller.
 */
template <>
cobalt::core::gfx::CameraController inline cobalt::core::gfx::CameraController::create<cobalt::core::gfx::OrthographicCamera>(
    const cobalt::core::gfx::CameraProperties& properties) {
    return CameraController(std::move(cobalt::createScope<OrthographicCamera>(properties.getCamera<OrthographicCamera>())),
                            properties.getLinearCling(), properties.getAngularCling(), properties.getZoomCling());
}
/** @brief: Create a first person perspective camera controller from the given properties.
 * @param properties: Properties of the camera.
 * @return: The camera controller.
 */
template <>
cobalt::core::gfx::CameraController inline cobalt::core::gfx::CameraController::create<cobalt::core::gfx::FPSCamera>(
    const cobalt::core::gfx::CameraProperties& properties) {
    return CameraController(std::move(cobalt::createScope<FPSCamera>(properties.getCamera<FPSCamera>())), properties.getLinearCling(),
                            properties.getAngularCling(), properties.getZoomCling());
}
/** @brief: Create a pivot camera controller from the given properties.
 * @param properties: Properties of the camera.
 * @return: The camera controller.
 */
template <>
cobalt::core::gfx::CameraController inline cobalt::core::gfx::CameraController::create<cobalt::core::gfx::PivotCamera>(
    const cobalt::core::gfx::CameraProperties& properties) {
    return CameraController(std::move(cobalt::createScope<PivotCamera>(properties.getCamera<PivotCamera>())), properties.getLinearCling(),
                            properties.getAngularCling(), properties.getZoomCling());
}