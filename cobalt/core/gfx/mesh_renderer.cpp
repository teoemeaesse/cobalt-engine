//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/mesh_renderer.h"


namespace cobalt {
    namespace core {
        void MeshRenderer::render(Mesh& mesh) const {
            mesh.getMaterial().bind();
            mesh.getVAO().bind();
            mesh.getIBO().bind();
            // TODO: bind material uniforms.
            glDrawElements((GLenum) mesh.getPrimitive(), mesh.getIBO().getCount(), GL_UNSIGNED_INT, nullptr);
        }
    }
}