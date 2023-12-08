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
             * @return: The render target.
             */
            RenderTarget(const TargetFBO* fbo, const Camera* camera);
            /* Destroy the render target.
             */
            ~RenderTarget() = default;

            /* Bind the render target.
             */
            void bind() const;

            /* Send the render target uniforms to a shader.
             * @param shader: The shader.
             */
            void sendUniforms(Shader& shader) const;

            /* Get the rendered texture.
             * @return: The texture.
             */
            const Texture& getTexture() const;

            private:
            const TargetFBO* fbo;   // Frame buffer object.
            const Camera* camera;   // Camera.
        };
    }
}