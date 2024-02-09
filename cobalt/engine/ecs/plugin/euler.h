// Created by tomas on
// 08-02-2024

#pragma once

#include "core/ecs/plugin/plugin.h"
#include "core/ecs/world.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief: Transform component. Contains position, rotation (euler) and scale.
         * @param x: World X position.
         * @param y: World Y position.
         * @param z: World Z position.
         * @param rotation: Euler rotation (degrees).
         * @param scale: Linear scale.
         */
        struct Transform : public core::ecs::Component {
            Transform(const float x, const float y, const float z, const glm::vec3 rotation, const glm::vec3 scale);
            Transform();

            float x, y, z;
            glm::vec3 rotation;
            glm::vec3 scale;
        };

        /**
         * @brief: Velocity component. Contains linear velocity.
         * @param x: X velocity.
         * @param y: Y velocity.
         * @param z: Z velocity.
         */
        struct Velocity : public core::ecs::Component {
            Velocity(const float x, const float y, const float z);
            Velocity();

            float x, y, z;
        };

        /**
         * @brief: AngularVelocity component. Contains angular velocity along each axis.
         * @param x: X angular velocity.
         * @param y: Y angular velocity.
         * @param z: Z angular velocity.
         */
        struct AngularVelocity : public core::ecs::Component {
            AngularVelocity(const float x, const float y, const float z);
            AngularVelocity();

            float x, y, z;
        };

        /**
         * @brief: Acceleration component. Contains linear acceleration.
         * @param x: X acceleration.
         * @param y: Y acceleration.
         * @param z: Z acceleration.
         */
        struct Acceleration : public core::ecs::Component {
            Acceleration(const float x, const float y, const float z);
            Acceleration();

            float x, y, z;
        };

        /**
         * @brief: AngularAcceleration component. Contains angular acceleration along each axis.
         * @param x: X angular acceleration.
         * @param y: Y angular acceleration.
         * @param z: Z angular acceleration.
         */
        struct AngularAcceleration : public core::ecs::Component {
            AngularAcceleration(const float x, const float y, const float z);
            AngularAcceleration();

            float x, y, z;
        };

        class EulerPlugin : public core::ecs::Plugin {
            public:
            /**
             * @brief: Initialize the plugin.
             * @param world: World instance.
             * @return: void
             */
            void onPlug(core::ecs::World& world) const noexcept override;
        };
    }  // namespace engine
}  // namespace cobalt