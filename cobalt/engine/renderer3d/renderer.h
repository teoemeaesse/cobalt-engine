// Created by tomas on
// 08-12-2023

#pragma once

#include "engine/render/target.h"
#include "engine/renderer3d/mesh.h"
#include "engine/renderer3d/skybox.h"

namespace cobalt {
    namespace engine {
        class Renderer {
            public:
            /**
             * @brief Create a renderer.
             * @return The renderer.
             */
            Renderer() noexcept;
            /**
             * @brief Destroy the renderer.
             */
            ~Renderer() noexcept = default;

            /**
             * @brief Render a mesh.
             * @param mesh The mesh to render.
             * @param target The render target to render to.
             * @param cameraManager The camera manager.
             */
            void renderMesh(Mesh& mesh, RenderTarget& target, const CameraManager& cameraManager) const;

            /**
             * @brief Render a skybox.
             * @param skybox The skybox to render.
             * @param target The render target to render to.
             * @param cameraManager The camera manager.
             */
            void renderSkybox(Skybox& skybox, RenderTarget& target, const CameraManager& cameraManager) const;

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
             * @return The texture unit.
             */
            void bindMaterial(const core::gfx::Material& material);

            /**
             * @brief Send all the bound textures to the shader.
             * @param shader The shader to send the uniforms to.
             */
            void sendUniforms(core::gl::Shader& shader) const;

            /**
             * @brief Unbind all texture units.
             */
            void clearTextureUnits();

            private:
            UMap<std::string, uint> textureUnits;  // Map of bound textures.
            uint currentUnit;                      // Current texture unit.
        };
    }  // namespace engine
}  // namespace cobalt