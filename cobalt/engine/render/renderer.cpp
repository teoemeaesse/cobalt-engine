/**
 * @file renderer.cpp
 * @brief A generic renderer interface.
 * @author Tomás Marques
 * @date 13-05-2024
 */

#include "engine/render/renderer.h"

#include "core/gl/context.h"
#include "engine/render/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Renderer::Renderer() noexcept : textureUnits(1), currentUnit(0) {}

        uint Renderer::getTextureUnit(const std::string& name) const {
            CB_CORE_WARN("Texture unit: " + name);
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                CB_CORE_WARN("Texture unit f: " + it->first);
                if (it->first == name) {
                    return it->second;
                }
            }
            throw core::ecs::PluginException<RenderPlugin, Renderer>("Named texture unit not found: " + name);
        }

        uint Renderer::bindTexture(const std::string& name, const gl::Texture& texture) {
            if (currentUnit >= gl::Context::queryMaxFragTextureUnits()) {
                throw core::ecs::PluginException<RenderPlugin, Renderer>("Maximum number of texture units exceeded");
            }
            texture.bindToUnit(currentUnit);
            textureUnits[name] = currentUnit++;
            return currentUnit - 1;
        }

        void Renderer::bindMaterial(const Material& material) {
            if (currentUnit + material.getTextures().size() > gl::Context::queryMaxFragTextureUnits()) {
                throw core::ecs::PluginException<RenderPlugin, Renderer>("Maximum number of texture units exceeded");
            }
            for (const auto& texture : material.getTextures()) {
                texture.second.bindToUnit(currentUnit);
                textureUnits[texture.first] = currentUnit++;
            }
        }

        void Renderer::clearTextureUnits() {
            textureUnits.clear();
            currentUnit = 0;
        }

        void Renderer::sendUniforms(gl::Shader& shader) const {
            for (auto it = textureUnits.begin(); it != textureUnits.end(); it++) {
                shader.setUniformInt("u_" + it->first, it->second);
            }
        }
    }  // namespace engine
}  // namespace cobalt