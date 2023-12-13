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
            textureUnits(1) {}

        void Renderer::render(Mesh& mesh, RenderTarget& target) const {
            mesh.getVAO().bind();
            mesh.getIBO().bind();
            Shader& shader = mesh.getMaterial().getShader();
            shader.use();
            target.bind();
            try {
                target.sendUniforms(shader);
                shader.setUniformMat4("u_model", mesh.getModelMatrix());
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
            for (uint i = 0; i < textureUnits.getSize(); i++) {
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
            textureUnits.push(name);
            return textureUnits.getSize() - 1;
        }

        void Renderer::clearTextureUnits() {
            textureUnits.clear();
        }
    }
}