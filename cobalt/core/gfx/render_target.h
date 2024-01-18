//
// Created
// by
// tomas
// on
// 08-12-2023.
//

#pragma once

#include "core/gfx/camera.h"
#include "core/gl/fbo.h"
#include "core/gl/ubo.h"

namespace cobalt {
    namespace core {
        class RenderTarget {
            public:
            /** @brief: Create a render target.
             * @param fbo: Frame buffer object to render to.
             * @param camera: The camera to render with.
             * @param name: The name of the render target.
             * @param cameraUBOBinding: The binding point for the camera UBO.
             * @return: The render target.
             */
            RenderTarget(const FBO& fbo, const Camera& camera, const std::string& name, const uint cameraUBOBinding);
            /** @brief: Destroy the render target.
             */
            ~RenderTarget() = default;
            /** @brief: Copy constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(const RenderTarget&);
            /** @brief: Move constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(RenderTarget&&);
            /** @brief: Copy assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(const RenderTarget&) = delete;
            /** @brief: Move assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(RenderTarget&&) = delete;

            /** @brief: Bind the render target.
             */
            void bind() const;

            /** @brief: Send the render target uniforms to a shader.
             * @param shader: The shader.
             */
            void sendUBO(const Shader& shader) const;

            /** @brief: Get the FBO.
             * @return: The FBO.
             */
            const FBO& getFBO() const;
            /** @brief: Get the name of the render target.
             * @return: The name.
             */
            const std::string& getName() const;
            /** @brief: Get the camera used to render.
             * @return: The camera.
             */
            const Camera& getCamera() const;

            private:
            const UBO ubo;         // Uniform buffer object.
            const FBO& fbo;        // Frame buffer object.
            const Camera& camera;  // The camera used to render.
            std::string name;      // Name of the render target. This is used to send uniforms for a render node that has a render target as a source.
        };
    }  // namespace core
}  // namespace
   // cobalt