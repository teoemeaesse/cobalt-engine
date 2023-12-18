//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/renderer.h"
#include "core/gfx/render_context.h"
#include "core/exceptions/gfx_exception.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        Renderer::Renderer() :
            textureUnits(1),
            currentUnit(0) {}

        void Renderer::renderMesh(Mesh& mesh, RenderTarget& target) const {
            mesh.bind();
            target.bind();
            Shader& shader = mesh.getMaterial().getShader();
            try {
                sendUniforms(shader);
                shader.setUniformVec3("lightPosition", glm::vec3(0.0, -45.0, 0.0));
                shader.setUniformVec3("lightColor", glm::vec3(5000.0, 5000.0, 5000.0));
                shader.setUniformVec3("camPos", target.getCamera().getPosition());
                target.sendUniforms(shader);
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                    shader.setUniformInt("u_" + it->first, it->second);
                }
            } catch (const GLException& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader. use UBOs.
            mesh.render();
        }
        
        void Renderer::renderSkybox(Skybox& skybox, RenderTarget& target) const {
            skybox.bind();
            target.bind();
            Shader& shader = skybox.getShader();
            try {
                sendUniforms(shader);
                shader.setUniformMat4("u_view", glm::mat4(glm::mat3(target.getCamera().getViewMatrix())));
                shader.setUniformMat4("u_projection", target.getCamera().getProjectionMatrix());
            } catch (const GLException& e) {
                CB_CORE_WARN(e.what());
            }
            RenderContext::disableDepthWriting();
            skybox.render();
            RenderContext::enableDepthWriting();
        }

        uint Renderer::getTextureUnit(const std::string& name) const {
            CB_CORE_WARN("Texture unit: " + name);
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                CB_CORE_WARN("Texture unit f: " + it->first);
                if (it->first == name) {
                    return it->second;
                }
            }
            throw GFXException("Texture not found");
        }

        uint Renderer::bindTexture(const std::string& name, const Texture& texture) {
            if (currentUnit >= RenderContext::queryMaxFragTextureUnits()) {
                throw GFXException("No more available texture units");
            }
            texture.bindToUnit(currentUnit);
            textureUnits[name] = currentUnit++;
            return currentUnit - 1;
        }

        void Renderer::clearTextureUnits() {
            textureUnits.clear();
            currentUnit = 0;
        }

        void Renderer::sendUniforms(Shader& shader) const {
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                shader.setUniformInt("u_" + it->first, it->second);
            }
        }
    }
}