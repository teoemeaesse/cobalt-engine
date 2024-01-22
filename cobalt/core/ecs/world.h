// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        class World {
            public:
            World() = default;
            ~World() = default;

            private:
            EntityRegistry entityRegistry;
            ComponentRegistry componentRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt