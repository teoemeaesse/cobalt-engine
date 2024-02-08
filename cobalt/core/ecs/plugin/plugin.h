// Created by tomas on
// 08-02-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class World;

        /**
         * @brief: Collection of systems, components and resources that can be easily added to / removed from an ECS world for self-contained
         * functionality.
         */
        class Plugin {
            public:
            virtual ~Plugin() = default;

            virtual void onPlug(World& world) const = 0;
        };
    }  // namespace core::ecs
}  // namespace cobalt