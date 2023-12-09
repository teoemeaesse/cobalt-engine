//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/mesh_renderer.h"


namespace cobalt {
    namespace core {
        MeshRenderer::MeshRenderer(RenderTarget& target) : target(target) {}

        void MeshRenderer::render(Mesh& mesh) const {
            target.bind();
            target.sendUniforms(mesh.getMaterial().use());
            mesh.getVAO().bind();
            mesh.getIBO().bind();
            glDrawElements((GLenum) mesh.getPrimitive(), mesh.getIBO().getCount(), GL_UNSIGNED_INT, nullptr);
        }

        void MeshRenderer::setTarget(RenderTarget& target) {
            this->target = target;
        }
    }
}