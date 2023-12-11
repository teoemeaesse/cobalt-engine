//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_target.h"
#include "core/exceptions/gfx_exception.h"


namespace cobalt {
    namespace core {
        RenderTarget::RenderTarget(const FBO& fbo, const Camera& camera, const std::string& name)
            : fbo(fbo),
              camera(camera),
              name(name) {
            if (name == "view" || name == "model" || name == "projection") {
                throw GFXException("Cannot use reserved name for render target");
            }
        }

        void RenderTarget::bind() const {
            fbo.bind();
        }

        void RenderTarget::sendUniforms(Shader& shader) const {
            shader.setUniformMat4("u_view", camera.getViewMatrix());
            shader.setUniformMat4("u_projection", camera.getProjectionMatrix());
            shader.setUniformInt("u_targetWidth", fbo.getWidth());
            shader.setUniformInt("u_targetHeight", fbo.getHeight());
        }

        const Texture& RenderTarget::getTexture() const {
            return dynamic_cast<const TargetFBO&>(fbo).getTexture();
        }

        const std::string& RenderTarget::getName() const {
            return name;
        }
    }
}