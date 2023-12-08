//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_target.h"


namespace cobalt {
    namespace core {
        RenderTarget::RenderTarget(const FBO* fbo, const Camera* camera)
            : fbo(fbo),
              camera(camera) {}

        void RenderTarget::bind() const {
            fbo->bind();
        }

        void RenderTarget::sendUniforms(Shader& shader) const {
            shader.setUniformMat4("u_view", camera->getViewMatrix());
            shader.setUniformMat4("u_projection", camera->getProjectionMatrix());
            shader.setUniformInt("u_targetWidth", fbo->getWidth());
            shader.setUniformInt("u_targetHeight", fbo->getHeight());
        }

        const GLHandle RenderTarget::getGLHandle() const {
            return dynamic_cast<const DefaultFBO*>(fbo) ? 0 : dynamic_cast<const TargetFBO*>(fbo)->getTexture().getGLHandle();
        }
    }
}