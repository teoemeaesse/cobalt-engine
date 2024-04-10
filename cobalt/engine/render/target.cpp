// Created by tomas on
// 08-12-2023

#include "engine/render/target.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        struct CameraUBO {
            glm::mat4 view;
            glm::mat4 projection;
            glm::vec3 position;
            int targetWidth;
            int targetHeight;
            glm::vec3 padding;
        };

        RenderTarget::RenderTarget(const gl::FBO& fbo, const CameraID camera, const std::string& name, const uint cameraUBOBinding)
            : fbo(fbo), camera(camera), name(name), ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), cameraUBOBinding) {
            if (name == "view" || name == "model" || name == "projection") {
                // throw gfx::GFXException("Cannot use reserved name for render target"); TODO: Add a plugin exception here
            }
        }

        RenderTarget::RenderTarget(const RenderTarget& other)
            : fbo(other.fbo), camera(other.camera), name(other.name), ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), 0) {}

        RenderTarget::RenderTarget(RenderTarget&& other) noexcept
            : fbo(Move(other.fbo)), camera(Move(other.camera)), name(Move(other.name)), ubo(gl::Usage::StaticDraw, sizeof(CameraUBO), 0) {}

        void RenderTarget::bind() const { fbo.bind(); }

        void RenderTarget::sendCameraUBO(const gl::Shader& shader, const CameraManager& cameraManager) const {
            ubo.bindToShader(shader, "Camera");
            const Camera& camera = cameraManager.getController(this->camera).getCamera();
            CameraUBO cameraUBO = {camera.getViewMatrix(), camera.getProjectionMatrix(), camera.getPosition(),
                                   (int)fbo.getWidth(),    (int)fbo.getHeight(),         glm::vec3(0.0)};
            ubo.load(&cameraUBO, sizeof(CameraUBO), 0);
        }

        const gl::FBO& RenderTarget::getFBO() const { return fbo; }

        const std::string& RenderTarget::getName() const { return name; }

        const CameraID& RenderTarget::getCameraID() const { return camera; }
    }  // namespace engine
}  // namespace cobalt