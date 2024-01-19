// Created by tomas on
// 05-12-2023

#pragma once

#include "core/gl/shader.h"

namespace cobalt {
    namespace core::gfx {
        /** @brief: A perspective or orthographic camera.
         */
        class Camera {
            public:
            /** @brief: Destroys the camera.
             */
            virtual ~Camera() = default;
            /** @brief: Copy constructor.
             * @param other: The camera to copy.
             * @return: The newly created camera.
             */
            Camera(const Camera&) = default;
            /** @brief: Move constructor.
             * @param other: The camera to move.
             * @return: The newly created camera.
             */
            Camera(Camera&&) = default;
            /** @brief: Copy assignment operator.
             * @param other: The camera to copy.
             * @return: The newly created camera.
             */
            Camera& operator=(const Camera&) = default;
            /** @brief: Move assignment operator.
             * @param other: The camera to move.
             * @return: The newly created camera.
             */
            Camera& operator=(Camera&&) = default;

            /** @brief: Calculates the view matrix of the camera.
             * @return: The view matrix of the camera.
             */
            const glm::mat4x4 getViewMatrix() const;
            /** @brief: Calculates the projection matrix of the camera.
             * @return: The projection matrix of the camera.
             */
            virtual const glm::mat4x4 getProjectionMatrix() const = 0;

            /** @brief: Gets the position of the camera in world space.
             * @return: The position of the camera in world space.
             */
            const glm::vec3 getPosition() const;

            /** @brief: Resizes the camera.
             * @param left: The left plane of the viewport.
             * @param right: The right plane of the viewport.
             * @param bottom: The bottom plane of the viewport.
             * @param top: The top plane of the viewport.
             */
            virtual void resize(const float left, const float right, const float bottom, const float top) = 0;
            /** @brief: Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            virtual void zoom(const float amount) = 0;
            /** @brief: Rotates the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            virtual void rotateHorizontal(const float amount) = 0;
            /** @brief: Rotates the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to rotate by (degrees).
             */
            virtual void rotateVertical(const float amount) = 0;
            /** @brief: Pans the camera by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            virtual void panDepth(const float amount) = 0;
            /** @brief: Pans the camera horizontally by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            virtual void panHorizontal(const float amount) = 0;
            /** @brief: Pans the camera vertically by the given amount.
             * The behaviour of this function is dependent on the specific type of camera.
             * @param amount: The amount to pan by.
             */
            virtual void panVertical(const float amount) = 0;

            protected:
            glm::vec3 position;   // The position of the camera in world space.
            glm::vec2 direction;  // The direction the camera is facing (degrees).
            float near,
                far;  // The near and far clipping planes.

            /** @brief: Creates a new camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             */
            Camera(const glm::vec3 position, const glm::vec2 direction, const float near, const float far);
        };

        /** @brief: A perspective camera.
         */
        class PerspectiveCamera : public Camera {
            public:
            /** @brief: Creates a new perspective camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180
             * looking right (+x) y: 0 looking down (-y), 90 looking forward (-z), 180
             * looking up (+y)
             * @param fov: The field of view of the camera (degrees).
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             * @param aspectRatio: The aspect ratio of the camera.
             */
            PerspectiveCamera(const glm::vec3 position, const glm::vec2 direction, const float fov, const float near, const float far,
                              const float aspectRatio);
            /** @brief: Destroys the camera.
             */
            ~PerspectiveCamera() = default;

            /** @brief: Resizes the camera.
             * @param aspectRatio: The new aspect ratio of the camera.
             */
            void resize(const float aspectRatio);

            /** @brief: Calculates the projection matrix of the camera.
             * @return: The projection matrix of the camera.
             */
            const glm::mat4x4 getProjectionMatrix() const override;

            protected:
            float fov;          // The field of view of the camera.
            float aspectRatio;  // The aspect ratio of the camera.

            private:
            /** @brief: Resizes the camera.
             * @param left: The left plane of the viewport.
             * @param right: The right plane of the viewport.
             * @param bottom: The bottom plane of the viewport.
             * @param top: The top plane of the viewport.
             */
            void resize(const float left, const float right, const float bottom, const float top) override;
        };

        /** @brief: An orthographic camera.
         */
        class OrthographicCamera : public Camera {
            public:
            /** @brief: Creates a new orthographic camera.
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             * @param left: The left clipping plane.
             * @param right: The right clipping plane.
             * @param bottom: The bottom clipping plane.
             * @param top: The top clipping plane.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             */
            OrthographicCamera(const glm::vec3 position, const glm::vec2 direction, const float left, const float right, const float bottom,
                               const float top, const float near, const float far);
            /** @brief: Destroys the camera.
             */
            ~OrthographicCamera() = default;

            /** @brief: Resizes the camera.
             * @param left: The left clipping plane.
             * @param right: The right clipping plane.
             * @param bottom: The bottom clipping plane.
             * @param top: The top clipping plane.
             */
            void resize(const float left, const float right, const float bottom, const float top) override;

            /** @brief: Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount) override;
            /** @brief: Rotates the camera horizontally by the given amount around the up vector.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount) override;
            /** @brief: Rotates the camera vertically by the given amount around the left vector.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount) override;
            /** @brief: Pans the camera by the given amount along the forward vector.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount) override;
            /** @brief: Pans the camera horizontally by the given amount along the right vector.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount) override;
            /** @brief: Pans the camera vertically by the given amount along the up vector.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount) override;

            /** @brief: Calculates the projection matrix of the camera.
             * @return: The projection matrix of the camera.
             */
            const glm::mat4x4 getProjectionMatrix() const override;

            private:
            float left,
                right;  // The left and right clipping planes.
            float bottom,
                top;           // The bottom and top clipping planes.
            float zoomFactor;  // The zoom factor of the camera.
        };

        class FPSCamera : public PerspectiveCamera {
            public:
            /** @brief: Creates a new FPS camera: a perspective camera with a fixed up vector (0,
             * 1, 0), where the direction is the direction the camera is facing (degrees).
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180
             * looking right (+x) y: 0 looking down (-y), 90 looking forward (-z), 180
             * looking up (+y)
             * @param fov: The field of view of the camera (degrees).
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             * @param aspectRatio: The aspect ratio of the camera.
             */
            FPSCamera(const glm::vec3 position, const glm::vec2 direction, const float fov, const float near, const float far,
                      const float aspectRatio);
            /** @brief: Destroys the camera.
             */
            ~FPSCamera() = default;

            /** @brief: Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount) override;
            /** @brief: Rotates the camera horizontally by the given amount around the up vector.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount) override;
            /** @brief: Rotates the camera vertically by the given amount around the left vector.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount) override;
            /** @brief: Pans the camera by the given amount along the forward vector.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount) override;
            /** @brief: Pans the camera horizontally by the given amount along the right vector.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount) override;
            /** @brief: Pans the camera vertically by the given amount along the up vector.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount) override;
        };

        class PivotCamera : public PerspectiveCamera {
            public:
            /** @brief: Creates a new pivot camera: a perspective camera with a fixed up vector
             * (0, 1, 0), where the direction is the direction the camera is facing
             * (degrees).
             * @param position: The position of the camera in world space.
             * @param direction: The direction the camera is facing (degrees).
             *                   x: 0 looking left (-x), 90 looking forward (-z), 180
             * looking right (+x) y: 0 looking down (-y), 90 looking forward (-z), 180
             * looking up (+y)
             * @param distance: The distance from the position of the camera to the the
             * center point. Zooming is done by changing this distance.
             * @param fov: The field of view of the camera (degrees). In this camera, the
             * FOV is fixed.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             * @param aspectRatio: The aspect ratio of the camera.
             */
            PivotCamera(const glm::vec3 position, const glm::vec2 direction, const float distance, const float fov, const float near, const float far,
                        const float aspectRatio);
            /** @brief: Creates a new pivot camera: a perspective camera with a fixed up vector
             * (0, 1, 0), pivoted on the center point.
             * @param position: The position of the camera in world space.
             * @param center: The center point the camera is pivoted around.
             * @param fov: The field of view of the camera (degrees). In this camera, the
             * FOV is fixed.
             * @param near: The near clipping plane.
             * @param far: The far clipping plane.
             * @param aspectRatio: The aspect ratio of the camera.
             */
            PivotCamera(const glm::vec3 position, const glm::vec3 center, const float fov, const float near, const float far,
                        const float aspectRatio);
            /** @brief: Destroys the camera.
             */
            ~PivotCamera() = default;

            /** @brief: Zooms the camera by the given amount.
             * @param amount: The amount to zoom by (fov degrees).
             */
            void zoom(const float amount) override;
            /** @brief: Rotates the camera horizontally by the given amount around the center
             * point.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateHorizontal(const float amount) override;
            /** @brief: Rotates the camera vertically by the given amount around the center point.
             * @param amount: The amount to rotate by (degrees).
             */
            void rotateVertical(const float amount) override;
            /** @brief: Pans the camera horizontally forward by the given amount.
             * @param amount: The amount to pan by.
             */
            void panDepth(const float amount) override;
            /** @brief: Pans the camera horizontally sideways by the given amount.
             * @param amount: The amount to pan by.
             */
            void panHorizontal(const float amount) override;
            /** @brief: Pans the camera vertically by the given amount along the up vector.
             * @param amount: The amount to pan by.
             */
            void panVertical(const float amount) override;

            private:
            float distance;  // The distance from the position of the camera to the the
                             // center point.
        };
    }  // namespace core::gfx
}  // namespace cobalt