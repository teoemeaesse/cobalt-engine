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
             * @param target: The render target.
             * @return: The renderer.
             */
            Renderer(RenderTarget& target);
            /* Destroy the renderer.
             */
            ~Renderer() = default;

            /* Render call.
             * @param mesh: The mesh to render.
             */
            void render(Mesh& mesh) const;

            /* Set the render target.
             * @param target: The render target.
             */
            void setTarget(RenderTarget& target);

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
            RenderTarget target;                // Render target.
            Vector<std::string> textureUnits;   // List of bound textures.
        };
    }
}