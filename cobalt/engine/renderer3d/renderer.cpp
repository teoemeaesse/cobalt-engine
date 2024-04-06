// Created by tomas on
// 08-12-2023

#include "engine/renderer3d/renderer.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Renderer::Renderer() : textureUnits(1), currentUnit(0) {}

        void Renderer::renderMesh(Mesh& mesh, RenderTarget& target) const {
            mesh.bind();
            target.bind();
            gl::Shader& shader = mesh.getMaterial().getShader();
            try {
                target.sendUBO(shader);
                shader.setUniformVec3("lightPosition", glm::vec3(0.0, 5.0, 0.0));
                shader.setUniformVec3("lightColor", glm::vec3(10000.0, 5000.0, 5000.0));
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                sendUniforms(shader);
            } catch (const gl::GLException& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader. use UBOs.
            mesh.render();
        }

        void Renderer::renderSkybox(Skybox& skybox, RenderTarget& target) const {
            skybox.bind();
            target.bind();
            gl::Shader& shader = skybox.getShader();
            try {
                sendUniforms(shader);
                target.sendUBO(shader);
            } catch (const gl::GLException& e) {
                CB_CORE_WARN(e.what());
            }
            gl::Context::disableDepthWriting();
            skybox.render();
            gl::Context::enableDepthWriting();
        }

        uint Renderer::getTextureUnit(const std::string& name) const {
            CB_CORE_WARN("Texture unit: " + name);
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                CB_CORE_WARN("Texture unit f: " + it->first);
                if (it->first == name) {
                    return it->second;
                }
            }
            throw gfx::GFXException("Texture not found");
        }

        uint Renderer::bindTexture(const std::string& name, const gl::Texture& texture) {
            if (currentUnit >= gl::Context::queryMaxFragTextureUnits()) {
                throw gfx::GFXException("No more available texture units");
            }
            texture.bindToUnit(currentUnit);
            textureUnits[name] = currentUnit++;
            return currentUnit - 1;
        }

        void Renderer::bindMaterial(const gfx::Material& material) {
            if (currentUnit + material.getTextures().size() > gl::Context::queryMaxFragTextureUnits()) {
                throw gfx::GFXException("No more available texture units");
            }
            for (const auto& texture : material.getTextures()) {
                texture.second.bindToUnit(currentUnit);
                textureUnits[texture.first] = currentUnit++;
            }
        }

        void Renderer::clearTextureUnits() {
            textureUnits.clear();
            currentUnit = 0;
        }

        void Renderer::sendUniforms(gl::Shader& shader) const {
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                shader.setUniformInt("u_" + it->first, it->second);
            }
        }
    }  // namespace engine
}  // namespace cobalt