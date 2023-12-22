//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_target.h"
#include "core/pch.h"


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

        RenderTarget::RenderTarget(const RenderTarget& other) : 
            fbo(other.fbo),
            camera(other.camera),
            name(other.name) {
        }

        RenderTarget::RenderTarget(RenderTarget&& other) : 
            fbo(std::move(other.fbo)),
            camera(std::move(other.camera)),
            name(std::move(other.name)) {
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

        const Texture& RenderTarget::getColorBuffer() const {
            return dynamic_cast<const TargetFBO&>(fbo).getColorBuffer();
        }

        const Texture& RenderTarget::getDepthBuffer() const {
            return dynamic_cast<const TargetFBO&>(fbo).getDepthBuffer();
        }

        const Texture& RenderTarget::getStencilBuffer() const {
            return dynamic_cast<const TargetFBO&>(fbo).getStencilBuffer();
        }

        const FBO& RenderTarget::getFBO() const {
            return fbo;
        }

        const std::string& RenderTarget::getName() const {
            return name;
        }

        const Camera& RenderTarget::getCamera() const {
            return camera;
        }
    }
}