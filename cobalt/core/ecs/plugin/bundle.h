/**
 * @file bundle.h
 * @brief A Bundle is a collection of plugins that can be added to a world.
 * @author Tomás Marques
 * @date 28-03-2024
 */

#pragma once

#include "core/ecs/plugin/plugin.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Implement this class to create a bundle of plugins that can be added to a world.
         */
        class Bundle {
            public:
            /**
             * @brief Default constructor.
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