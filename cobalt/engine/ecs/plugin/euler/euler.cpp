// Created by tomas on
// 08-02-2024

#include "engine/ecs/plugin/euler/euler.h"

#include "engine/ecs/plugin/time/plugin.h"

using namespace cobalt::core::ecs;

namespace cobalt {
    namespace engine {
        Transform::Transform(const float x, const float y, const float z, const glm::vec3 rotation, const glm::vec3 scale) noexcept
            : x(x), y(y), z(z), rotation(rotation), scale(scale) {}

        Transform::Transform() noexcept : x(0.0f), y(0.0f), z(0.0f), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)) {}

        Velocity::Velocity(const float x, const float y, const float z) noexcept : x(x), y(y), z(z) {}

        Velocity::Velocity() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

        AngularVelocity::AngularVelocity(const float x, const float y, const float z) noexcept : x(x), y(y), z(z) {}

        AngularVelocity::AngularVelocity() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

        Acceleration::Acceleration(const float x, const float y, const float z) noexcept : x(x), y(y), z(z) {}

        Acceleration::Acceleration() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

        AngularAcceleration::AngularAcceleration(const float x, const float y, const float z) noexcept : x(x), y(y), z(z) {}

        AngularAcceleration::AngularAcceleration() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
    }  // namespace engine
}  // namespace cobalt