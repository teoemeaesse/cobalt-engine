//
// Created by tomas on 05-12-2023.
//

#include "core/gfx/camera.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        Camera::Camera(const glm::vec3 position, const glm::vec2 direction, const float angularSpeed, const float near, const float far)
            : position(position), direction(direction), angularSpeed(angularSpeed), near(near), far(far)
        {}

        const glm::mat4x4 Camera::getViewMatrix() const {
            float theta = glm::radians(180.0f + direction.x);
            float phi = glm::radians(180.0f - direction.y);
            glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            glm::vec3 z = glm::normalize(position - center);
            glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 x = glm::normalize(glm::cross(y, z));
            y = glm::normalize(glm::cross(z, x));
            return {
                x.x,                     y.x,                     z.x,                     0.0f,
                x.y,                     y.y,                     z.y,                     0.0f, 
                x.z,                     y.z,                     z.z,                     0.0f,
                -glm::dot(position, x),  -glm::dot(position, y),  -glm::dot(position, z),  1.0f,
            };
        }
        
        const glm::vec3 Camera::getPosition() const {
            return position;
        }

        PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec2 direction, const float fov, const float angularSpeed, const float near, const float far, const float aspectRatio)
            : Camera(position, direction, angularSpeed, near, far), fov(fov), aspectRatio(aspectRatio)
        {}

        void PerspectiveCamera::resize(const float aspectRatio) {
            this->aspectRatio = aspectRatio;
        }

        const glm::mat4x4 PerspectiveCamera::getProjectionMatrix() const {
            float tan_half_fov = tan(glm::radians(fov) / 2.0f);
            return glm::mat4x4 {
                1.0f / (aspectRatio * tan_half_fov),  0.0f,                0.0f,                               0.0f,
                0.0f,                                 1.0f / tan_half_fov, 0.0f,                               0.0f,
                0.0f,                                 0.0f,                (near + far) / (near - far),        -1.0f,
                0.0f,                                 0.0f,                (2.0f * near * far) / (near - far), 0.0f
            };
        }

        OrthographicCamera::OrthographicCamera(const glm::vec3 position, const glm::vec2 direction, const float angularSpeed, const float left, const float right, const float bottom, const float top, const float near, const float far)
            : Camera(position, direction, angularSpeed, near, far), left(left), right(right), bottom(bottom), top(top)
        {}

        void OrthographicCamera::resize(const float left, const float right, const float bottom, const float top) {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
        }

        const glm::mat4x4 OrthographicCamera::getProjectionMatrix() const {
            return glm::mat4x4 {
                2.0f / (right - left),           0.0f,                            0.0f,                        0.0f,
                0.0f,                            2.0f / (top - bottom),           0.0f,                        0.0f,
                0.0f,                            0.0f,                            2.0f / (near - far),         0.0f,
                (left + right) / (left - right), (bottom + top) / (bottom - top), (near + far) / (near - far), 1.0f
            };
        }

        void OrthographicCamera::rotateHorizontal(const float amount) {
            direction.x += amount * angularSpeed;
        }

        void OrthographicCamera::rotateVertical(const float amount) {
            const float newPhi = direction.y + amount * angularSpeed;
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

        FPSCamera::FPSCamera(
                    const glm::vec3 position,
                    const glm::vec2 direction,
                    const float fov,
                    const float angularSpeed,
                    const float near, const float far,
                    const float aspectRatio) : PerspectiveCamera(position, direction, fov, angularSpeed, near, far, aspectRatio) {
            assert(fov > 30.0f && fov < 150.0f);
        }

        void FPSCamera::zoom(const float amount) {
            const float newFov = fov + amount;
            if (30.0f < newFov && newFov < 150.0f) {
                fov = newFov;
            }
        }

        void FPSCamera::rotateHorizontal(const float amount) {
            direction.x += amount * angularSpeed;
        }

        void FPSCamera::rotateVertical(const float amount) {
            const float newPhi = direction.y + amount * angularSpeed;
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

        PivotCamera::PivotCamera(
                    const glm::vec3 position,
                    const glm::vec2 direction,
                    const float distance,
                    const float fov,
                    const float angularSpeed,
                    const float near, const float far,
                    const float aspectRatio) : PerspectiveCamera(position, direction, fov, angularSpeed, near, far, aspectRatio),
                    distance(distance) {
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
            direction.x += amount * angularSpeed;
            const glm::vec3 center = position + (glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi)) * distance);
            float rot = glm::radians(-amount * angularSpeed);
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 k = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 v_rot = pivotToCamera * cos(rot) +
                            glm::cross(k, pivotToCamera) * sin(rot) +
                            k * (glm::dot(k, pivotToCamera)) * (1 - cos(rot));
            position = center + v_rot;
        }

        void PivotCamera::rotateVertical(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            direction.y += amount * angularSpeed;
            const glm::vec3 center = position + (glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi)) * distance);
            float rot = glm::radians(-amount * angularSpeed);
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 k = glm::normalize(glm::cross(pivotToCamera, glm::vec3(0.0f, 1.0f, 0.0f)));
            glm::vec3 v_rot = pivotToCamera * cos(rot) +
                            glm::cross(k, pivotToCamera) * sin(rot) +
                            k * (glm::dot(k, pivotToCamera)) * (1 - cos(rot));
            position = center + v_rot;
        }

        void PivotCamera::panDepth(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            glm::vec3 forward = position - center; // vector from center to camera
            forward.y = 0.0f; // remove the vertical component
            forward = glm::normalize(forward); // normalize the vector
            position += forward * amount; // move position along the horizontal plane
        }

        void PivotCamera::panHorizontal(const float amount) {
            const float theta = glm::radians(180.0f + direction.x);
            const float phi = glm::radians(180.0f - direction.y);
            const glm::vec3 center = position + glm::vec3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
            glm::vec3 pivotToCamera = position - center;
            glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), pivotToCamera)); // right vector
            position += right * amount; // move position
        }

        void PivotCamera::panVertical(const float amount) {
            position += glm::vec3(0.0f, 1.0f, 0.0f) * amount; // move up/down
        }
    }
}