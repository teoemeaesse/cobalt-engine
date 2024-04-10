// Created by tomas on
// 28-03-2024

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace core::ecs {
        class Bundle {
            public:
            /**
             * @brief Default constructor.
             * @return Bundle
             */
            Bundle() noexcept = default;
            /**
             * @brief Default destructor.
             */
            virtual ~Bundle() noexcept = default;

            /**
             * @brief Add plugins to the world.
             * @param world The world to add the plugins to.
             */
            virtual void addPlugins(World& world) noexcept = 0;
        };
    }  // namespace core::ecs
}  // namespace cobalt