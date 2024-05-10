// Created by tomas on
// 06-04-2024

#include "engine/euler/plugin.h"

#include "engine/euler/euler.h"
#include "engine/time/plugin.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        EulerPlugin::EulerPlugin() noexcept : Plugin(TITLE, "Provides basic euler integration for linear and angular motion.", TimePlugin{}) {}

        void EulerPlugin::onPlug(ecs::World& world) const noexcept {
            world.registerComponent<Transform>();
            world.registerComponent<Velocity>();
            world.registerComponent<Acceleration>();
            world.registerComponent<AngularVelocity>();
            world.registerComponent<AngularAcceleration>();

            /**
             * @brief Euler integration system.
             */
            world.addSystem<ecs::Query<Transform&, const Velocity&>, ecs::ReadRequest<Time>>(ecs::DefaultSchedules::Update,
                                                                                             [](auto query, auto time) {
                                                                                                 const float deltaTime = time->getDeltaTime();
                                                                                                 for (auto [transform, velocity] : query) {
                                                                                                     transform.x += velocity.x * deltaTime;
                                                                                                     transform.y += velocity.y * deltaTime;
                                                                                                     transform.z += velocity.z * deltaTime;
                                                                                                 }
                                                                                             });
            /**
             * @brief Euler integration system.
             */
            world.addSystem<ecs::Query<Velocity&, const Acceleration&>, ecs::ReadRequest<Time>>(ecs::DefaultSchedules::Update,
                                                                                                [](auto query, auto time) {
                                                                                                    const float deltaTime = time->getDeltaTime();
                                                                                                    for (auto [velocity, acceleration] : query) {
                                                                                                        velocity.x += acceleration.x * deltaTime;
                                                                                                        velocity.y += acceleration.y * deltaTime;
                                                                                                        velocity.z += acceleration.z * deltaTime;
                                                                                                    }
                                                                                                });
            /**
             * @brief Euler integration system.
             */
            world.addSystem<ecs::Query<Transform&, const AngularVelocity&>, ecs::ReadRequest<Time>>(
                ecs::DefaultSchedules::Update, [](auto query, auto time) {
                    const float deltaTime = time->getDeltaTime();
                    for (auto [transform, angularVelocity] : query) {
                        transform.rotation.x += angularVelocity.x * deltaTime;
                        transform.rotation.y += angularVelocity.y * deltaTime;
                        transform.rotation.z += angularVelocity.z * deltaTime;
                    }
                });
            /**
             * @brief Euler integration system.
             */
            world.addSystem<ecs::Query<AngularVelocity&, const AngularAcceleration&>, ecs::ReadRequest<Time>>(
                ecs::DefaultSchedules::Update, [](auto query, auto time) {
                    const float deltaTime = time->getDeltaTime();
                    for (auto [angularVelocity, angularAcceleration] : query) {
                        angularVelocity.x += angularAcceleration.x * deltaTime;
                        angularVelocity.y += angularAcceleration.y * deltaTime;
                        angularVelocity.z += angularAcceleration.z * deltaTime;
                    }
                });
        }
    }  // namespace engine
}  // namespace cobalt