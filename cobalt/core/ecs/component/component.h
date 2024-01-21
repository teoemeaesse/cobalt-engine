// Created by tomas on
// 18-01-2024

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        class Component {
            public:
            using ID = uint64;    // Component ID - unique between all components.
            using Type = uint64;  // Component type - unique between different component types.

            /** @brief: Default constructor.
             * @param type: Component type.
             * @param id: Component ID.
             * @return: Component instance.
             */
            Component(const Type type, const ID id) noexcept;

            private:
            Type type;
            ID id;
        };
    }  // namespace core::ecs
}  // namespace cobalt