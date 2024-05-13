// Created by tomas on
// 08-12-2023

#include "engine/raster3d/renderer.h"

#include "core/exception.h"
#include "core/gl/context.h"
#include "engine/raster3d/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Raster3D::Raster3D() noexcept : Renderer(), cameraUBO(gl::Usage::DynamicDraw, sizeof(Camera::UBO)) {}

        void Raster3D::render(RenderTarget& target) const {}

        void Raster3D::renderMesh(Mesh& mesh, RenderTarget& target) const {
            mesh.bind();
            target.bind();
            gl::Shader& shader = mesh.getMaterial().getShader();
            try {
                shader.setUniformVec3("lightPosition", glm::vec3(0.0, 5.0, 0.0));
                shader.setUniformVec3("lightColor", glm::vec3(10000.0, 5000.0, 5000.0));
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sendUniforms(shader);
                cameraUBO.bind();
                cameraUBO.bindToShader(shader, "Camera", 0);
            } catch (const CoreException<Raster3D>& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader. use UBOs.
            mesh.render();
        }

        void Raster3D::renderSkybox(Skybox& skybox, RenderTarget& target) const {
            skybox.bind();
            target.bind();
            gl::Shader& shader = skybox.getShader();
            try {
                sendUniforms(shader);
                cameraUBO.bind();
                cameraUBO.bindToShader(shader, "Camera", 0);
            } catch (const CoreException<Raster3D>& e) {
                CB_CORE_WARN(e.what());
            }
            gl::Context::disableDepthWriting();
            skybox.render();
            gl::Context::enableDepthWriting();
        }

        void Raster3D::loadCameraUBO(const Camera::UBO& data) const {
            cameraUBO.bind();
            cameraUBO.load(&data, sizeof(Camera::UBO), 0);
        }
    }  // namespace engine
}  // namespace cobalt