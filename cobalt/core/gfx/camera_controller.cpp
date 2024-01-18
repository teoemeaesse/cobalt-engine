//
// Created
// by
// tomas
// on
// 28-12-2023.
//

#include "core/gfx/camera_controller.h"

namespace cobalt {
    namespace core::gfx {
        CameraProperties::CameraProperties()
            : type(Type::Free),
              position(glm::vec3(0.0f)),
              direction(glm::vec2(90.0f, 90.0f)),
              linearCling(1.0f),
              linearVelocity(25.0f),
              angularCling(1.0f),
              angularVelocity(5.0f),
              zoomCling(1.0f),
              zoomVelocity(1.0f),
              fov(90.0f),
              aspectRatio(16.0f / 9.0f),
              distance(50.0f),
              near(1.0f),
              far(1000.0f),
              left(-100.0f),
              right(100.0f),
              top(100.0f),
              bottom(-100.0f) {}

        CameraProperties& CameraProperties::setType(const Type type) {
            this->type = type;
            return *this;
        }

        CameraProperties& CameraProperties::setPosition(const glm::vec3& position) {
            this->position = position;
            return *this;
        }

        CameraProperties& CameraProperties::setCenter(const glm::vec3& center) {
            this->center = center;
            return *this;
        }

        CameraProperties& CameraProperties::setDirection(const glm::vec2& direction) {
            this->direction = direction;
            return *this;
        }

        CameraProperties& CameraProperties::setLinearCling(const float linearCling) {
            this->linearCling = linearCling;
            return *this;
        }

        CameraProperties& CameraProperties::setLinearVelocity(const float linearVelocity) {
            this->linearVelocity = linearVelocity;
            return *this;
        }

        CameraProperties& CameraProperties::setAngularCling(const float angularCling) {
            this->angularCling = angularCling;
            return *this;
        }

        CameraProperties& CameraProperties::setAngularVelocity(const float angularVelocity) {
            this->angularVelocity = angularVelocity;
            return *this;
        }

        CameraProperties& CameraProperties::setZoomCling(const float zoomCling) {
            this->zoomCling = zoomCling;
            return *this;
        }

        CameraProperties& CameraProperties::setZoomVelocity(const float zoomVelocity) {
            this->zoomVelocity = zoomVelocity;
            return *this;
        }

        CameraProperties& CameraProperties::setFOV(const float fov) {
            this->fov = fov;
            return *this;
        }

        CameraProperties& CameraProperties::setAspectRatio(const float aspectRatio) {
            this->aspectRatio = aspectRatio;
            return *this;
        }

        CameraProperties& CameraProperties::setDistance(const float distance) {
            this->distance = distance;
            return *this;
        }

        CameraProperties& CameraProperties::setClippingPlanes(const float near, const float far) {
            this->near = near;
            this->far = far;
            return *this;
        }

        CameraProperties& CameraProperties::setOrthoPlanes(const float left, const float right, const float top, const float bottom) {
            this->left = left;
            this->right = right;
            this->top = top;
            this->bottom = bottom;
            return *this;
        }

        const CameraProperties::Type CameraProperties::getType() const { return type; }

        const glm::vec3& CameraProperties::getPosition() const { return position; }

        const glm::vec3& CameraProperties::getCenter() {
            if (!center.has_value()) {
                const float theta = glm::radians(180.0f + direction.x);
                const float phi = glm::radians(180.0f - direction.y);
                this->center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            }
            return center.value();
        }

        const glm::vec2& CameraProperties::getDirection() const { return direction; }

        const float CameraProperties::getLinearCling() const { return linearCling; }

        const float CameraProperties::getLinearVelocity() const { return linearVelocity; }

        const float CameraProperties::getAngularCling() const { return angularCling; }

        const float CameraProperties::getAngularVelocity() const { return angularVelocity; }

        const float CameraProperties::getZoomCling() const { return zoomCling; }

        const float CameraProperties::getZoomVelocity() const { return zoomVelocity; }

        const float CameraProperties::getFOV() const { return fov; }

        const float CameraProperties::getAspectRatio() const { return aspectRatio; }

        const float CameraProperties::getDistance() const { return distance; }

        const float CameraProperties::getNear() const { return near; }

        const float CameraProperties::getFar() const { return far; }

        const float CameraProperties::getLeft() const { return left; }

        const float CameraProperties::getRight() const { return right; }

        const float CameraProperties::getTop() const { return top; }

        const float CameraProperties::getBottom() const { return bottom; }

        Camera& CameraController::getCamera() const { return *camera; }

        void CameraController::update() {
            camera->zoom(deltaZoom * zoomCling);
            camera->rotateHorizontal(deltaAngular.x * angularCling);
            camera->rotateVertical(deltaAngular.y * angularCling);
            camera->panDepth(deltaLinear.z * linearCling);
            camera->panHorizontal(deltaLinear.x * linearCling);
            camera->panVertical(deltaLinear.y * linearCling);
            deltaZoom *= 1.0f - zoomCling;
            deltaAngular *= 1.0f - angularCling;
            deltaLinear *= 1.0f - linearCling;
        }

        void CameraController::resize(const float left, const float right, const float bottom, const float top) {
            camera->resize(left, right, bottom, top);
        }

        void CameraController::resize(const float aspectRatio) { camera->resize(0.0f, aspectRatio, 0.0f, 1.0f); }

        void CameraController::zoom(const float amount) { deltaZoom += amount; }

        void CameraController::rotateHorizontal(const float amount) { deltaAngular.x += amount; }

        void CameraController::rotateVertical(const float amount) { deltaAngular.y += amount; }

        void CameraController::panDepth(const float amount) { deltaLinear.z += amount; }

        void CameraController::panHorizontal(const float amount) { deltaLinear.x += amount; }

        void CameraController::panVertical(const float amount) { deltaLinear.y += amount; }

        CameraController::CameraController(Scope<Camera> camera, const float linearCling, const float angularCling, const float zoomCling)
            : camera(std::move(camera)),
              deltaLinear(glm::vec3(0.0f)),
              deltaAngular(glm::vec2(0.0f)),
              deltaZoom(0.0f),
              linearCling(linearCling * linearCling),
              angularCling(angularCling * angularCling),
              zoomCling(zoomCling * zoomCling) {}

        CameraController& CameraManager::getCamera(const CameraID id) {
            try {
                return cameras.at(id);
            } catch (const std::out_of_range& e) {
                throw GFXException("Camera with id " + std::to_string(id) + " does not exist");
            }
        }

        CameraController& CameraManager::getCamera(const std::string& name) {
            try {
                return cameras.at(cameraNames.at(name));
            } catch (const std::out_of_range& e) {
                throw GFXException("Camera with name " + name + " does not exist");
            }
        }
    }  // namespace core
} // namespace cobalt