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
             * @brief Create a render target.
             * @param fbo Frame buffer object to render to.
             * @param name The name of the render target.
             * @param camera The camera to render with.
             */
            RenderTarget(const core::gl::FBO& fbo, const std::string& name, const CameraID camera);
            /**
             * @brief Default destructor.
             */
            ~RenderTarget() = default;
            /**
             * @brief Copy constructor.
             * @param other The other render target.
             */
            RenderTarget(const RenderTarget& other);
            /**
             * @brief Move constructor.
             * @param other The other render target.
             */
            RenderTarget(RenderTarget&& other) noexcept;
            /**
             * @brief Copy assignment.
             * @param other The other render target.
             * @return The render target.
             */
            RenderTarget& operator=(const RenderTarget& other) = delete;
            /**
             * @brief Move assignment.
             * @param other The other render target.
             * @return The render target.
             */
            RenderTarget& operator=(RenderTarget&& other) = delete;

            /**
             * @brief Bind the render target.
             */
            void bind() const;

            /**
             * @brief Get the FBO.
             * @return FBO
             */
            const core::gl::FBO& getFBO() const;
            /**
             * @brief Get the name of the render target.
             * @return std::string
             */
            const std::string& getName() const;
            /**
             * @brief Get the camera to render with.
             * @return CameraID
             */
            const CameraID getCameraID() const;

            private:
            const core::gl::FBO& fbo;  // Frame buffer object.
            const std::string name;    // Name of the render target.
            const CameraID cameraID;   // The camera to render with.
        };
    }  // namespace engine
}  // namespace cobalt