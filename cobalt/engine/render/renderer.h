/**
 * @file renderer.h
 * @brief A generic renderer interface.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#pragma once

#include "core/gfx/material.h"
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
             * @brief Render to a target.
             * @param target The target to render to.
             */
            virtual void render(RenderTarget& target) const = 0;

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
            void bindMaterial(const core::gfx::Material& material);

            /**
             * @brief Unbind all texture units.
             */
            void clearTextureUnits();

            /**
             * @brief Send all the bound textures to the shader.
             * @param shader The shader to send the uniforms to.
             */
            void sendUniforms(core::gl::Shader& shader) const;

            private:
            UMap<std::string, uint> textureUnits;  ///< Map of bound textures.
            uint currentUnit;                      ///< Current texture unit.
        };
    }  // namespace engine
}  // namespace cobalt