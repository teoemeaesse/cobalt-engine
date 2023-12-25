//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/render_target.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        struct CameraUBO {
            glm::mat4 view;
            glm::mat4 projection;
            int targetWidth;
            int targetHeight;
            glm::vec2 padding;
        };

        RenderTarget::RenderTarget(const FBO& fbo,
                                   const Camera& camera,
                                   const std::string& name,
                                   const uint cameraUBOBinding)
            : fbo(fbo),
              camera(camera),
              name(name),
              ubo(GLUsage::StaticDraw, sizeof(CameraUBO), cameraUBOBinding) {
            if (name == "view" || name == "model" || name == "projection") {
                throw GFXException("Cannot use reserved name for render target");
            }
        }

        RenderTarget::RenderTarget(const RenderTarget& other) : 
            fbo(other.fbo),
            camera(other.camera),
            name(other.name),
            ubo(GLUsage::StaticDraw, sizeof(CameraUBO), 0) {
        }

        RenderTarget::RenderTarget(RenderTarget&& other) : 
            fbo(std::move(other.fbo)),
            camera(std::move(other.camera)),
            name(std::move(other.name)),
            ubo(GLUsage::StaticDraw, sizeof(CameraUBO), 0) {
        }

        void RenderTarget::bind() const {
            fbo.bind();
        }

        void RenderTarget::sendUBO(const Shader& shader) const {
            ubo.bindToShader(shader, "Camera");
            CameraUBO cameraUBO = {
                camera.getViewMatrix(),
                camera.getProjectionMatrix(),
                (int) fbo.getWidth(),
                (int) fbo.getHeight(),
                glm::vec2(0.0)
            };
            ubo.load(&cameraUBO, sizeof(CameraUBO), 0);
            fbo.bind();
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