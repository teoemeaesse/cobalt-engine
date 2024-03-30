// Created by tomas on
// 30-03-2024

#pragma once

#include "engine/ecs/plugin/euler/euler.h"
#include "engine/ecs/plugin/time/plugin.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Euler integration plugin. Provides basic euler integration for linear and angular motion.
         */
        class EulerPlugin : public core::ecs::Plugin {
            public:
            static inline constexpr const char* TITLE = "Euler integration";

            /**
             * @brief: Construct the plugin.
             * @return: EulerPlugin
             */
            EulerPlugin() noexcept : Plugin(TITLE, "Provides basic euler integration for linear and angular motion.", TimePlugin{}) {}

            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override {
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
                world.addSystem<Query<RefMut<Transform>, Ref<AngularVelocity>>, ReadRequest<Time>>(
                    DefaultSchedules::Update, [](auto query, auto time) {
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
        };
    }  // namespace engine
}  // namespace cobalt