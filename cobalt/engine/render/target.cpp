// Created by tomas on
// 08-12-2023

#include "engine/render/target.h"

#include "engine/render/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        RenderTarget::RenderTarget(const gl::FBO& fbo, const std::string& name) : fbo(fbo), name(name) {
            if (name == "view" || name == "model" || name == "projection") {
                throw ecs::PluginException<RenderPlugin, RenderTarget>("Cannot use reserved name for render target");
            }
        }

        RenderTarget::RenderTarget(const RenderTarget& other) : fbo(other.fbo), name(other.name) {}

        RenderTarget::RenderTarget(RenderTarget&& other) noexcept : fbo(Move(other.fbo)), name(Move(other.name)) {}

        void RenderTarget::bind() const { fbo.bind(); }

        const gl::FBO& RenderTarget::getFBO() const { return fbo; }

        const std::string& RenderTarget::getName() const { return name; }
    }  // namespace engine
}  // namespace cobalt