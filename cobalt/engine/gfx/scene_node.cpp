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

            // TODO: set up lighting via scene graph. this is just a placeholder
            PointLight plight1(10000, Colors::Yellow);
            PointLight plight2(10000, Colors::Blue);
            PointLight plight3(10000, Colors::Red);
            PointLight::UBO plightUBO(core::gl::Usage::StaticDraw);
            plightUBO.bind();
            plightUBO.emplace<PointLight::Serial>(plight1, glm::vec3(0.0, 0.0, 0.0));
            plightUBO.emplace<PointLight::Serial>(plight2, glm::vec3(0.0, 50.0, 0.0));
            plightUBO.emplace<PointLight::Serial>(plight3, glm::vec3(50.0, 0.0, 0.0));
            plightUBO.emplace<PointLight::Serial>(plight1, glm::vec3(100.0, 0.0, 0.0));
            plightUBO.emplace<PointLight::Serial>(plight2, glm::vec3(0.0, 0.0, 100.0));
            plightUBO.emplace<PointLight::Serial>(plight3, glm::vec3(0.0, 100.0, 100.0));
            plightUBO.emplace<PointLight::Serial>(plight1, glm::vec3(100.0, 100.0, 0.0));
            plightUBO.emplace<PointLight::Serial>(plight2, glm::vec3(50.0, 0.0, 100.0));
            plightUBO.emplace<PointLight::Serial>(plight3, glm::vec3(100.0, 100.0, 100.0));
            plightUBO.emplace<PointLight::Serial>(plight3, glm::vec3(100.0, -50.0, 100.0));
            plightUBO.send();
            for (uint i = 0; i < meshes.size(); i++) {
                RenderNode::renderMesh(meshes[i], plightUBO);
            }
        }

        void SceneNode::onResize(const float width, const float height) {
            // Empty
        }
    }  // namespace engine
}  // namespace cobalt