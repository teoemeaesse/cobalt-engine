//
// Created by tomas on 08-12-2023.
//

#include "core/gfx/mesh.h"


namespace cobalt {
    namespace core {
        Mesh::Mesh(const VAO& vao, const IBO& ibo, const Material& material, const GLPrimitive& primitive)
        : vao(vao),
          ibo(ibo),
          material(material),
          primitive(primitive),
          worldTranslate(0.0f),
          worldRotate(0.0f),
          worldScale(1.0f) {
        }

        void Mesh::translate(const glm::vec3& translation) {
            this->worldTranslate += translation;
        }

        void Mesh::rotate(const glm::vec3& rotation) {
            this->worldRotate += rotation;
        }

        void Mesh::scale(const glm::vec3& scale) {
            this->worldScale *= scale;
        }

        glm::mat4x4 Mesh::getModelMatrix() const {
            const float cx = cos(worldRotate.x);
            const float sx = sin(worldRotate.x);
            const float cy = cos(worldRotate.y);
            const float sy = sin(worldRotate.y);
            const float cz = cos(worldRotate.z);
            const float sz = sin(worldRotate.z);

            return {
                worldScale.x * cz * cy, worldScale.x * (cz * sy * sx - cx * sz), worldScale.x * (cx * cz * sy + sx * sz), 0.0f,
                worldScale.y * sz * cy, worldScale.y * (sx * sy * sz + cx * cz), worldScale.y * (cx * sy * sz - cz * sx), 0.0f,
                -worldScale.z * sy,     worldScale.z * cy * sx,                  worldScale.z * cx * cy,                  0.0f,
                worldTranslate.x,       worldTranslate.y,                        worldTranslate.z,                        1.0f
            };
        }

        VAO& Mesh::getVAO() {
            return this->vao;
        }

        IBO& Mesh::getIBO() {
            return this->ibo;
        }

        Material& Mesh::getMaterial() {
            return this->material;
        }

        GLPrimitive Mesh::getPrimitive() const {
            return this->primitive;
        }
    }
}