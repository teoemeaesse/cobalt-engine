//
// Created by tomas on 05-12-2023.
//

#pragma once

#include "core/gl/shader.h"


namespace cobalt {
    namespace core {
        /* A perspective or orthographic camera.
         */
        class Camera {
            friend class PerspectiveCamera;
            friend class OrthographicCamera;
            
            public:
            /* Destroys the camera.
             */
            ~Camera() = default;

            /* Calculates the view matrix of the camera.
             * @return The view matrix of the camera.
             */
            const glm::mat4x4 getViewMatrix() const;
            /* Calculates the projection matrix of the camera.
             * @return The projection matrix of the camera.
             */
            virtual const glm::mat4x4 getProjectionMatrix() const = 0;

            /* Rotates the camera horizontally by the given amount.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount);
            /* Rotates the camera vertically by the given amount.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount);
            /* Pans the camera by the given amount.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount);
            /* Pans the camera horizontally by the given amount.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount);
            /* Pans the camera vertically by the given amount.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount);

            protected:
            glm::vec3 position;     // The position of the camera in world space.
            glm::vec2 direction;    // The direction the camera is facing (degrees).
            float angularSpeed;     // The angular speed of the camera.
            float near, far;        // The near and far clipping planes.
            float aspectRatio;      // The aspect ratio of the camera.

            private:
            /* Creates a new camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             * @param angularSpeed: The angular speed of the camera.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             */
            Camera(const glm::vec3 position, const glm::vec2 direction, const float angularSpeed, const float near, const float far);
        };

        /* A perspective camera.
         */
        class PerspectiveCamera : public Camera {
            public:
            /* Creates a new perspective camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180 looking right (+x)
             *                   y: 0 looking down (-y), 90 looking forward (-z), 180 looking up (+y)
             * @param fov: The field of view of the camera (degrees).
             * @param angularSpeed: The angular speed of the camera.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             * @param aspectRatio: The aspect ratio of the camera.
             */
            PerspectiveCamera(const glm::vec3 position, const glm::vec2 direction, const float fov, const float angularSpeed, const float near, const float far, const float aspectRatio);
            /* Destroys the camera.
             */
            ~PerspectiveCamera() = default;

            /* Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount);

            /* Resizes the camera.
             * @param aspectRatio: The new aspect ratio of the camera.
             */
            void resize(const float aspectRatio);

            /* Calculates the projection matrix of the camera.
             * @return The projection matrix of the camera.
             */
            const glm::mat4x4 getProjectionMatrix() const override;

            private:
            float fov;              // The field of view of the camera.
            float aspectRatio;      // The aspect ratio of the camera.
        };

        /* An orthographic camera.
         */
        class OrthographicCamera : public Camera {
            public:
            /* Creates a new orthographic camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             * @param angularSpeed: The angular speed of the camera.
             * @param left: The left clipping plane.
             * @param right: The right clipping plane.
             * @param bottom: The bottom clipping plane.
             * @param top: The top clipping plane.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             */
            OrthographicCamera(const glm::vec3 position,
                               const glm::vec2 direction,
                               const float angularSpeed,
                               const float left,
                               const float right,
                               const float bottom,
                               const float top,
                               const float near,
                               const float far);
            /* Destroys the camera.
             */
            ~OrthographicCamera() = default;

            /* Resizes the camera.
             * @param left: The left clipping plane.
             * @param right: The right clipping plane.
             * @param bottom: The bottom clipping plane.
             * @param top: The top clipping plane.
             */
            void resize(const float left, const float right, const float bottom, const float top);
            
            /* Calculates the projection matrix of the camera.
             * @return The projection matrix of the camera.
             */
            const glm::mat4x4 getProjectionMatrix() const override;

            private:
            float left, right;      // The left and right clipping planes.
            float bottom, top;      // The bottom and top clipping planes.
        };
    }
}