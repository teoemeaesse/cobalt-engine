//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/mesh.h"
#include "core/gfx/render_target.h"
#include "core/containers/vector.h"


namespace cobalt {
    namespace core {
        class Renderer {
            public:
            /* Create a renderer.
             * @return: The renderer.
             */
            Renderer();
            /* Destroy the renderer.
             */
            ~Renderer() = default;

            /* Render call.
             * @param mesh: The mesh to render.
             * @param target: The render target to render to.
             */
            void render(Mesh& mesh, RenderTarget& target) const;

            /* Get the bound texture unit of a given named texture.
             * @param name: The name of the texture.
             * @return: The texture unit it is bound to.
             */
            uint getTextureUnit(const std::string& name) const;

            /* Bind a texture to the next available texture unit.
             * Throws an exception if there are no more available texture units.
             * @param name: The name of the texture.
             * @param texture: The texture.
             * @return: The texture unit.
             */
            uint bindTexture(const std::string& name, const Texture& texture);

            /* Unbind all texture units.
             */
            void clearTextureUnits();

            private:
            Vector<std::string> textureUnits;   // List of bound textures.
        };
    }
}