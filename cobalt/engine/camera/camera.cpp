// Created by tomas on
// 05-12-2023

#include "engine/camera/camera.h"

namespace cobalt {
    namespace engine {
        Camera::Serial::Serial() noexcept : view(0), projection(0), position(0), targetWidth(0), targetHeight(0), _(0) {}

        Camera::Serial::Serial(const Camera& camera, const core::gl::FBO& target) noexcept
            : view(camera.getViewMatrix()),
              projection(camera.getProjectionMatrix()),
              position(camera.getPosition()),
              targetWidth(target.getWidth()),
              targetHeight(target.getHeight()),
              _(glm::vec3(0.0f)) {}

        Camera::Camera(const glm::vec3 position, const glm::vec2 direction, const float near, const float far)
            : position(position), direction(direction), near(near), far(far) {}

        const glm::mat4x4 Camera::getViewMatrix() const {
            float theta = glm::radians(180.0f + direction.x);
            float phi = glm::radians(180.0f - direction.y);
            glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            glm::vec3 z = glm::normalize(position - center);
            glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 x = glm::normalize(glm::cross(y, z));
            y = glm::normalize(glm::cross(z, x));
            return {
                x.x,
                y.x,
                z.x,
                0.0f,
                x.y,
                y.y,
                z.y,
                0.0f,
                x.z,
                y.z,
                z.z,
                0.0f,
                -glm::dot(position, x),
                -glm::dot(position, y),
                -glm::dot(position, z),
                1.0f,
            };
        }

        const glm::vec3 Camera::getPosition() const { return position; }

        Camera::UBO::UBO(const core::gl::Usage usage) : core::gl::UBO(usage, sizeof(Serial)) {}

        PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec2 direction, const float fov, const float near, const float far,
                                             const float aspectRatio)
            : Camera(position, direction, near, far), fov(fov), aspectRatio(aspectRatio) {}

        void PerspectiveCamera::resize(const float aspectRatio) { this->aspectRatio = aspectRatio; }

        void PerspectiveCamera::resize(const float left, const float right, const float bottom, const float top) {
            resize((right - left) / (top - bottom));
        }

        const glm::mat4x4 PerspectiveCamera::getProjectionMatrix() const {
            float tan_half_fov = tan(glm::radians(fov) / 2.0f);
            return glm::mat4x4{1.0f / (aspectRatio * tan_half_fov),
                               0.0f,
                               0.0f,
                               0.0f,
                               0.0f,
                               1.0f / tan_half_fov,
                               0.0f,
                               0.0f,
                               0.0f,
                               0.0f,
                               (near + far) / (near - far),
                               -1.0f,
                               0.0f,
                               0.0f,
                               (2.0f * near * far) / (near - far),
                               0.0f};
        }

        OrthographicCamera::OrthographicCamera(const glm::vec3 position, const glm::vec2 direction, const float left, const float right,
                                               const float bottom, const float top, const float near, const float far)
            : Camera(position, direction, near, far), left(left), right(right), bottom(bottom), top(top), zoomFactor(1.0f) {}

        void OrthographicCamera::resize(const float left, const float right, const float bottom, const float top) {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
        }

        const glm::mat4x4 OrthographicCamera::getProjectionMatrix() const {
            const float left = this->left * zoomFactor;
            const float right = this->right * zoomFactor;
            const float bottom = this->bottom * zoomFactor;
            const float top = this->top * zoomFactor;
            return glm::mat4x4{2.0f / (right - left),
                               0.0f,
                               0.0f,
                               0.0f,
                               0.0f,
                               2.0f / (top - bottom),
                               0.0f,
                               0.0f,
                               0.0f,
                               0.0f,
                               2.0f / (near - far),
                               0.0f,
                               (left + right) / (left - right),
                               (bottom + top) / (bottom - top),
                               (near + far) / (near - far),
                               1.0f};
        }

        void OrthographicCamera::zoom(const float amount) { zoomFactor += amount; }

        void OrthographicCamera::rotateHorizontal(const float amount) { direction.x += amount; }

        void OrthographicCamera::rotateVertical(const float amount) {
            const float newPhi = direction.y + amount;
            if (0.0f < newPhi && newPhi < 180.0f) {
                direction.y = newPhi;
            }
        }

        void OrthographicCamera::panDepth(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            const glm::vec3 forward = position - center;
            position += forward * amount;
        }

        void OrthographicCamera::panHorizontal(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            const glm::vec3 forward = position - center;
            const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            const glm::vec3 left = glm::normalize(glm::cross(up, forward));
            position += left * amount;
        }

        void OrthographicCamera::panVertical(const float amount) {
            const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            position += up * amount;
        }

        FPSCamera::FPSCamera(const glm::vec3 position, const glm::vec2 direction, const float fov, const float near, const float far,
                             const float aspectRatio)
            : PerspectiveCamera(position, direction, fov, near, far, aspectRatio) {
            assert(fov > 30.0f && fov < 150.0f);
        }

        void FPSCamera::zoom(const float amount) {
            const float newFov = fov + amount;
            if (30.0f < newFov && newFov < 150.0f) {
                fov = newFov;
            }
        }

        void FPSCamera::rotateHorizontal(const float amount) { direction.x += amount; }

        void FPSCamera::rotateVertical(const float amount) {
            const float newPhi = direction.y + amount;
            if (0.0f < newPhi && newPhi < 180.0f) {
                direction.y = newPhi;
            }
        }

        void FPSCamera::panDepth(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            const glm::vec3 forward = position - center;
            position += forward * amount;
        }

        void FPSCamera::panHorizontal(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            const glm::vec3 forward = position - center;
            const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            const glm::vec3 left = glm::normalize(glm::cross(up, forward));
            position += left * amount;
        }

        void FPSCamera::panVertical(const float amount) {
            const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            position += up * amount;
        }

        static const glm::vec2 getSpherical(const glm::vec3& position, const glm::vec3& center) {
            if (position == center) {
                return glm::vec2(90.0f, 90.0f);
            }
            glm::vec3 diff = glm::normalize(position - center);
            float theta = glm::degrees(std::atan2(diff.z, diff.x));
            float phi = glm::degrees(std::asin(diff.y));
            return glm::vec2(theta, phi);
        }

        PivotCamera::PivotCamera(const glm::vec3 position, const glm::vec2 direction, const float distance, const float fov, const float near,
                                 const float far, const float aspectRatio)
            : PerspectiveCamera(position, direction, fov, near, far, aspectRatio), distance(distance) {
            assert(distance > 0.0f);
        }

        PivotCamera::PivotCamera(const glm::vec3 position, const glm::vec3 center, const float fov, const float near, const float far,
                                 const float aspectRatio)
            : PerspectiveCamera(position, getSpherical(position, center), fov, near, far, aspectRatio), distance(glm::length(position - center)) {
            assert(distance > 0.0f);
        }

        void PivotCamera::zoom(const float amount) {
            float newDistance = distance + amount;
            if (newDistance > near && newDistance < far / 2.0f) {
                distance = newDistance;
                const float theta = glm::radians(180.0f + direction.x);
                const float phi = glm::radians(180.0f - direction.y);
                const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
                const glm::vec3 forward = position - center;
                position += forward * amount;
            }
        }

        void PivotCamera::rotateHorizontal(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            direction.x += amount * 10.0f;
            const glm::vec3 center = position + (glm::vec3(cosf(theta) * sinf(phi), cosf(phi), sinf(theta) * sinf(phi)) * distance);
            float rot = glm::radians(-amount * 10.0f);
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 k = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 v_rot =
                pivotToCamera * cosf(rot) + glm::cross(k, pivotToCamera) * sinf(rot) + k * (glm::dot(k, pivotToCamera)) * (1 - cosf(rot));
            position = center + v_rot;
        }

        void PivotCamera::rotateVertical(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            direction.y += amount * 10.0f;
            const glm::vec3 center = position + (glm::vec3(cosf(theta) * sinf(phi), cosf(phi), sinf(theta) * sinf(phi)) * distance);
            float rot = glm::radians(-amount * 10.0f);
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 k = glm::normalize(glm::cross(pivotToCamera, glm::vec3(0.0f, 1.0f, 0.0f)));
            glm::vec3 v_rot =
                pivotToCamera * cosf(rot) + glm::cross(k, pivotToCamera) * sinf(rot) + k * (glm::dot(k, pivotToCamera)) * (1 - cosf(rot));
            position = center + v_rot;
        }

        void PivotCamera::panDepth(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cosf(theta) * sinf(phi), cosf(phi), sinf(theta) * sinf(phi));
            glm::vec3 forward = position - center;  // vector from center to camera
            forward.y = 0.0f;                       // remove the vertical component
            forward = glm::normalize(forward);      // normalize the vector
            position += forward * amount;           // move position along the horizontal plane
        }

        void PivotCamera::panHorizontal(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cosf(theta) * sinf(phi), cosf(phi), sinf(theta) * sinf(phi));
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f),
                                                        pivotToCamera));  // right vector
            position += right * amount;                                   // move position
        }

        void PivotCamera::panVertical(const float amount) {
            position += glm::vec3(0.0f, 1.0f,
                                  0.0f) * amount;  // move up/down
        }
    }  // namespace engine
}  // namespace cobalt
