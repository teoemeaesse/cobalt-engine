// Created by tomas on
// 08-02-2024

#include "engine/ecs/plugin/euler.h"

#include "engine/ecs/plugin/time.h"

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

        EulerPlugin::EulerPlugin() noexcept : Plugin("Euler integration", "Provides basic euler integration for linear and angular motion.") {}

        void EulerPlugin::onPlug(core::ecs::World& world) const noexcept {
            world.registerComponent<Transform>();
            world.registerComponent<Velocity>();
            world.registerComponent<Acceleration>();
            world.registerComponent<AngularVelocity>();
            world.registerComponent<AngularAcceleration>();

            /**
             * @brief: Euler integration system.
             */
            world.addSystem<Query<RefMut<Transform>, Ref<Velocity>>, ReadRequest<Time>>(DefaultSchedules::Update, [](auto query, auto time) {
                const float deltaTime = time.get().deltaTime;
                for (auto [transform, velocity] : query) {
                    transform.x += velocity.x * deltaTime;
                    transform.y += velocity.y * deltaTime;
                    transform.z += velocity.z * deltaTime;
                }
            });
            /**
             * @brief: Euler integration system.
             */
            world.addSystem<Query<RefMut<Velocity>, Ref<Acceleration>>, ReadRequest<Time>>(DefaultSchedules::Update, [](auto query, auto time) {
                const float deltaTime = time.get().deltaTime;
                for (auto [velocity, acceleration] : query) {
                    velocity.x += acceleration.x * deltaTime;
                    velocity.y += acceleration.y * deltaTime;
                    velocity.z += acceleration.z * deltaTime;
                }
            });
            /**
             * @brief: Euler integration system.
             */
            world.addSystem<Query<RefMut<Transform>, Ref<AngularVelocity>>, ReadRequest<Time>>(DefaultSchedules::Update, [](auto query, auto time) {
                const float deltaTime = time.get().deltaTime;
                for (auto [transform, angularVelocity] : query) {
                    transform.rotation.x += angularVelocity.x * deltaTime;
                    transform.rotation.y += angularVelocity.y * deltaTime;
                    transform.rotation.z += angularVelocity.z * deltaTime;
                }
            });
            /**
             * @brief: Euler integration system.
             */
            world.addSystem<Query<RefMut<AngularVelocity>, Ref<AngularAcceleration>>, ReadRequest<Time>>(
                DefaultSchedules::Update, [](auto query, auto time) {
                    const float deltaTime = time.get().deltaTime;
                    for (auto [angularVelocity, angularAcceleration] : query) {
                        angularVelocity.x += angularAcceleration.x * deltaTime;
                        angularVelocity.y += angularAcceleration.y * deltaTime;
                        angularVelocity.z += angularAcceleration.z * deltaTime;
                    }
                });
        }
    }  // namespace engine
}  // namespace cobalt