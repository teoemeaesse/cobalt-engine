// Created by tomas on
// 08-12-2023

#include "engine/raster3d/renderer.h"

#include "core/gl/context.h"
#include "core/utils/exception.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Raster3D::Raster3D() noexcept : Renderer() {}

        void Raster3D::render(Mesh& mesh, gl::UBO& pointLighting) const {
            mesh.bind();
            gl::Shader& shader = mesh.getMaterial().getShader();
            try {
                // shader.setUniformVec3("lightPosition", glm::vec3(0.0, 5.0, 0.0));
                // shader.setUniformVec3("lightColor", glm::vec3(10000.0, 5000.0, 10000.0));
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                    shader.setUniformInt("u_" + it->first, it->second);
                }
                cameraUBO.bindToShader(shader, "Camera", 0);
                pointLighting.bindToShader(shader, "PointLighting", 1);
            } catch (const CoreException<Raster3D>& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader.
            mesh.render();
        }

        void Raster3D::render(Mesh& mesh) const {
            mesh.bind();
            gl::Shader& shader = mesh.getMaterial().getShader();
            try {
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                    shader.setUniformInt("u_" + it->first, it->second);
                }
                cameraUBO.bindToShader(shader, "Camera", 0);
            } catch (const CoreException<Raster3D>& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader.
            mesh.render();
        }
    }  // namespace engine
}  // namespace cobalt
