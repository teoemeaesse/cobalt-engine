// Created by tomas on
// 08-12-2023

#include "engine/mesh3d/mesh.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        Mesh::Mesh(gl::VAO&& vao, gl::IBO&& ibo, Material& material, const gl::Primitive& primitive)
            : vao(Move(vao)), ibo(Move(ibo)), material(material), primitive(primitive), worldTranslate(0.0f), worldRotate(0.0f), worldScale(1.0f) {}

        Mesh::Mesh(Mesh&& other) noexcept
            : vao(Move(other.vao)),
              ibo(Move(other.ibo)),
              material(other.material),
              primitive(other.primitive),
              worldTranslate(other.worldTranslate),
              worldRotate(other.worldRotate),
              worldScale(other.worldScale) {}

        void Mesh::translate(const glm::vec3& translation) { this->worldTranslate += translation; }

        void Mesh::rotate(const glm::vec3& rotation) { this->worldRotate += rotation; }

        void Mesh::scale(const glm::vec3& scale) { this->worldScale *= scale; }

        glm::mat4x4 Mesh::getModelMatrix() const {
            const glm::vec3 rotation = glm::radians(this->worldRotate);
            const float cx = cos(rotation.x);
            const float sx = sin(rotation.x);
            const float cy = cos(rotation.y);
            const float sy = sin(rotation.y);
            const float cz = cos(rotation.z);
            const float sz = sin(rotation.z);

            return {worldScale.x * cz * cy,
                    worldScale.x * (cz * sy * sx - cx * sz),
                    worldScale.x * (cx * cz * sy + sx * sz),
                    0.0f,
                    worldScale.y * sz * cy,
                    worldScale.y * (sx * sy * sz + cx * cz),
                    worldScale.y * (cx * sy * sz - cz * sx),
                    0.0f,
                    -worldScale.z * sy,
                    worldScale.z * cy * sx,
                    worldScale.z * cx * cy,
                    0.0f,
                    worldTranslate.x,
                    worldTranslate.y,
                    worldTranslate.z,
                    1.0f};
        }

        void Mesh::bind() const {
            this->vao.bind();
            this->ibo.bind();
            this->material.getShader().use();
        }

        void Mesh::render() const { glDrawElements((GLenum)this->primitive, this->ibo.getCount(), GL_UNSIGNED_INT, nullptr); }

        Material& Mesh::getMaterial() { return this->material; }

        gl::Primitive Mesh::getPrimitive() const { return this->primitive; }
    }  // namespace engine
}  // namespace cobalt