//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/renderer.h"
#include "core/gfx/render_context.h"
#include "core/exceptions/gfx_exception.h"
#include "core/utils/log.h"
#include "engine/internal/texture_library.h"


namespace cobalt {
    namespace core {
        Renderer::Renderer() :
            textureUnits(1) {}

        void Renderer::render(Mesh& mesh, RenderTarget& target) const {
            mesh.getVAO().bind();
            mesh.getIBO().bind();
            Shader& shader = mesh.getMaterial().getShader();
            shader.use();
            target.bind();
            try {
                shader.setUniformInt("u_source_scene", 0);
                shader.setUniformInt("u_albedo", 6);
                shader.setUniformInt("u_normal", 7);
                shader.setUniformInt("u_mrao", 8);
                shader.setUniformVec3("lightPosition", glm::vec3(0.0, -49.0, 0.0));
                shader.setUniformVec3("lightColor", glm::vec3(5000.0, 1000.0, 1000.0));
                shader.setUniformVec3("camPos", target.getCamera().getPosition());
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-albedo")).bindToUnit(6);
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-normal")).bindToUnit(7);
                CB_TEXTURE_LIBRARY.getTexture(CB_TEXTURE_LIBRARY.getTextureID("wood-mrao")).bindToUnit(8);
                target.sendUniforms(shader);
                const glm::mat4& model = mesh.getModelMatrix();
                shader.setUniformMat4("u_model", model);
                shader.setUniformMat3("u_normal_matrix", glm::transpose(glm::inverse(glm::mat3(model))));
                for (uint i = 0; i < textureUnits.getSize(); i++) {
                    shader.setUniformInt("u_" + textureUnits[i], i);
                }
            } catch (const GLException& e) {
                CB_CORE_WARN(e.what());
            }
            // TODO: inject uniforms into shader. use UBOs.
            glDrawElements((GLenum) mesh.getPrimitive(), mesh.getIBO().getCount(), GL_UNSIGNED_INT, nullptr);
        }

        uint Renderer::getTextureUnit(const std::string& name) const {
            CB_CORE_WARN("Texture unit: " + name);
            for (uint i = 0; i < textureUnits.getSize(); i++) {
                CB_CORE_WARN("Texture unit f: " + textureUnits[i]);
                if (textureUnits[i] == name) {
                    return i;
                }
            }
            throw GFXException("Texture not found");
        }

        uint Renderer::bindTexture(const std::string& name, const Texture& texture) {
            if (textureUnits.getSize() >= RenderContext::queryMaxFragTextureUnits()) {
                throw GFXException("No more available texture units");
            }
            texture.bindToUnit(textureUnits.getSize());
            textureUnits.push(std::string(name));
            return textureUnits.getSize() - 1;
        }

        void Renderer::clearTextureUnits() {
            textureUnits.clear();
        }
    }
}