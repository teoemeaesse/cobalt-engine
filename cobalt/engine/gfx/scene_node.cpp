// Created by tomas on
// 10-12-2023

#include "engine/gfx/scene_node.h"

#include "core/gl/context.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        SceneNode::SceneNode(Scene& scene, Raster3D& renderer) : RenderNode(renderer), scene(scene) {}

        void SceneNode::render() {
            gl::Context::disableDepthWriting();
            auto& skybox = scene.getSkybox();
            if (skybox.has_value()) {
                RenderNode::renderMesh(skybox.value());
            }
            gl::Context::enableDepthWriting();
            auto& meshes = scene.getMeshes();

            // shader.setUniformVec3("lightPosition", glm::vec3(0.0, 5.0, 0.0));
            // shader.setUniformVec3("lightColor", glm::vec3(10000.0, 5000.0, 10000.0));
            // TODO: set up lighting via scene graph. this is just a placeholder
            PointLight::UBO<1> plightUBO(core::gl::Usage::StaticDraw);
            plightUBO.bind();
            plightUBO.emplace<PointLight>(10000, Colors::Red);
            for (uint i = 0; i < meshes.size(); i++) {
                RenderNode::renderMesh(meshes[i], plightUBO);
            }
            core::gl::Context::checkGLErrors();
            core::gl::Context::clearGLErrors();
        }

        void SceneNode::onResize(const float width, const float height) {
            // Empty
        }
    }  // namespace engine
}  // namespace cobalt