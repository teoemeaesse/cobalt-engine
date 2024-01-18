//
// Created
// by
// tomas
// on
// 08-12-2023.
//

#include "core/gfx/render_target.h"

#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
        struct CameraUBO {
            glm::mat4 view;
            glm::mat4 projection;
            glm::vec3 position;
            int targetWidth;
            int targetHeight;
            glm::vec3 padding;
        };

        RenderTarget::RenderTarget(const gl::FBO& fbo, const Camera& camera, const std::string& name, const uint cameraUBOBinding)
            : fbo(fbo), camera(camera), name(name), ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), cameraUBOBinding) {
            if (name == "view" || name == "model" || name == "projection") {
                throw GFXException("Cannot use reserved name for render target");
            }
        }

        RenderTarget::RenderTarget(const RenderTarget& other)
            : fbo(other.fbo), camera(other.camera), name(other.name), ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), 0) {}

        RenderTarget::RenderTarget(RenderTarget&& other)
            : fbo(std::move(other.fbo)),
              camera(std::move(other.camera)),
              name(std::move(other.name)),
              ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), 0) {}

        void RenderTarget::bind() const { fbo.bind(); }

        void RenderTarget::sendUBO(const gl::Shader& shader) const {
            ubo.bindToShader(shader, "Camera");
            CameraUBO cameraUBO = {camera.getViewMatrix(), camera.getProjectionMatrix(), camera.getPosition(),
                                   (int)fbo.getWidth(),    (int)fbo.getHeight(),         glm::vec3(0.0)};
            ubo.load(&cameraUBO, sizeof(CameraUBO), 0);
        }

        const gl::FBO& RenderTarget::getFBO() const { return fbo; }

        const std::string& RenderTarget::getName() const { return name; }

        const Camera& RenderTarget::getCamera() const { return camera; }
    }  // namespace core::gfx
}  // namespace cobalt