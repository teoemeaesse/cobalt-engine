//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_target.h"
#include "core/exceptions/gfx_exception.h"


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

        const Texture& RenderTarget::getTexture() const {
            auto texture = dynamic_cast<const TargetFBO*>(fbo);
            if (!texture) {
                throw GFXException("Cannot get texture from default fbo");
            }
            return texture->getTexture();
        }
    }
}