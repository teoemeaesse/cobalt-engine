// Created by tomas on
// 08-02-2024

#pragma once

#include "core/core.h"

namespace cobalt {
    namespace engine {
        class Application;

        /**
         * @brief Time resource.
         * @param deltaTime Time since last frame (seconds).
         * @param elapsedTime Time since application startup (seconds).
         */
        class Time : public core::ecs::Resource {
            friend class Application;

            public:
            /**
             * @brief Creates a new Time resource.
             * @return Time
             */
            Time() noexcept;

            /**
             * @brief Returns the time since last frame (seconds).
             * @return float
             */
            float getDeltaTime() const noexcept;
            /**
             * @brief Returns the time since application startup (seconds).
             * @return float
             */
            float getElapsedTime() const noexcept;

            private:
            float deltaTime;
            float elapsedTime;
        };
    }  // namespace engine
}  // namespace cobalt