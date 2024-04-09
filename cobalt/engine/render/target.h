// Created by tomas on
// 08-12-2023

#pragma once

#include "core/gl/fbo.h"
#include "core/gl/ubo.h"
#include "engine/camera/plugin.h"

namespace cobalt {
    namespace engine {
        class RenderTarget {
            public:
            /**
             * @brief: Create a render target.
             * @param fbo: Frame buffer object to render to.
             * @param camera: The ID for the camera to render with.
             * @param name: The name of the render target.
             * @param cameraUBOBinding: The binding point for the camera UBO.
             * @return: The render target.
             */
            RenderTarget(const core::gl::FBO& fbo, const CameraID camera, const std::string& name, const uint cameraUBOBinding);
            /**
             * @brief: Destroy the render target.
             */
            ~RenderTarget() = default;
            /**
             * @brief: Copy constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(const RenderTarget&);
            /**
             * @brief: Move constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(RenderTarget&&) noexcept;
            /**
             * @brief: Copy assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(const RenderTarget&) = delete;
            /**
             * @brief: Move assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(RenderTarget&&) = delete;

            /**
             * @brief: Bind the render target.
             * @return: void
             */
            void bind() const;

            /**
             * @brief: Send the render target's camera UBO to the shader.
             * @param shader: The shader.
             * @param cameraManager: The camera manager containing the camera.
             * @return: void
             */
            void sendCameraUBO(const core::gl::Shader& shader, const CameraManager& cameraManager) const;

            /**
             * @brief: Get the FBO.
             * @return: FBO
             */
            const core::gl::FBO& getFBO() const;
            /**
             * @brief: Get the name of the render target.
             * @return: std::string
             */
            const std::string& getName() const;
            /**
             * @brief: Get the ID for the camera used to render.
             * @return: CameraID
             */
            const CameraID& getCameraID() const;

            private:
            const core::gl::UBO ubo;   // Uniform buffer object.
            const core::gl::FBO& fbo;  // Frame buffer object.
            const CameraID camera;     // The camera used to render.
            const std::string
                name;  // Name of the render target. This is used to send uniforms for a render node that has a render target as a source.
        };
    }  // namespace engine
}  // namespace cobalt