/**
 * @file renderer.h
 * @brief A generic renderer interface.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#pragma once

#include "engine/material/material.h"
#include "engine/mesh3d/mesh.h"
#include "engine/render/target.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A generic renderer interface for rendering to a RenderTarget.
         */
        class Renderer {
            public:
            /**
             * @brief Creates a new Renderer.
             */
            Renderer() noexcept;
            /**
             * @brief Default destructor.
             */
            virtual ~Renderer() noexcept = default;

            /**
             * @brief Start rendering to a target.
             * @param camera The camera to render render with.
             * @param target The target to render to.
             */
            virtual void start(const Camera& camera, RenderTarget& target);

            /**
             * @brief Render to a target.
             * @param mesh The mesh to render.
             * @param pointLighting The point lights to illuminate the scene with.
             */
            virtual void render(Mesh& mesh, core::gl::UBO& pointLighting) const = 0;

            /**
             * @brief Render to a target, no lighting.
             * @param mesh The mesh to render.
             */
            virtual void render(Mesh& mesh) const = 0;

            /**
             * @brief Get the bound texture unit of a given named texture.
             * @param name The name of the texture.
             * @return The texture unit it is bound to.
             */
            uint getTextureUnit(const std::string& name) const;

            /**
             * @brief Bind a texture to the next available texture unit.
             * Throws an exception if there are no more available texture units.
             * @param name The name of the texture.
             * @param texture The texture.
             * @return The texture unit.
             */
            uint bindTexture(const std::string& name, const core::gl::Texture& texture);

            /**
             * @brief Bind a material's textures to the next available texture units.
             * Throws an exception if there are no more available texture units.
             * @param material The material to bind.
             */
            void bindMaterial(const Material& material);

            /**
             * @brief Unbind all texture units.
             */
            void clearTextureUnits();

            protected:
            UMap<std::string, uint> textureUnits;  ///< Map of bound textures.
            uint currentUnit;                      ///< Current texture unit.
            Camera::UBO cameraUBO;                 ///< The camera UBO.
        };
    }  // namespace engine
}  // namespace cobalt