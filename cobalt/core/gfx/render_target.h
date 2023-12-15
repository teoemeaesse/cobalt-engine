//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gl/fbo.h"
#include "core/gfx/camera.h"


namespace cobalt {
    namespace core {
        class RenderTarget {
            public:
            /* Create a render target.
             * @param fbo: Frame buffer object to render to.
             * @param camera: The camera to render with.
             * @param name: The name of the render target.
             * @return: The render target.
             */
            RenderTarget(const FBO& fbo, const Camera& camera, const std::string& name);
            /* Destroy the render target.
             */
            ~RenderTarget() = default;
            /* Copy constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(const RenderTarget&);
            /* Move constructor.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget(RenderTarget&&);
            /* Copy assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(const RenderTarget&) = delete;
            /* Move assignment.
             * @param other: The other render target.
             * @return: The render target.
             */
            RenderTarget& operator=(RenderTarget&&) = delete;

            /* Bind the render target.
             */
            void bind() const;

            /* Send the render target uniforms to a shader.
             * @param shader: The shader.
             */
            void sendUniforms(Shader& shader) const;

            /* Get the texture for the color buffer.
             * This will throw an exception if the fbo is the default fbo.
             * @return: The texture.
             */
            const Texture& getColorBuffer() const;
            /* Get the texture for the depth buffer.
             * This will throw an exception if the fbo is the default fbo.
             * @return: The texture.
             */
            const Texture& getDepthBuffer() const;
            /* Get the texture for the stencil buffer.
             * This will throw an exception if the fbo is the default fbo.
             * @return: The texture.
             */
            const Texture& getStencilBuffer() const;
            /* Get the FBO.
             * @return: The FBO.
             */
            const FBO& getFBO() const;
            /* Get the name of the render target.
             * @return: The name.
             */
            const std::string& getName() const;
            
            const Camera& getCamera() const;

            private:
            const FBO& fbo;         // Frame buffer object.
            const Camera& camera;   // Camera.
            std::string name;       // Name of the render target. This is used to send uniforms for a 
                                    // render node that has a render target as a source.
        };
    }
}