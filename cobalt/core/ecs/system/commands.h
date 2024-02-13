// Created by tomas on
// 13-02-2024

#pragma once

#include "core/ecs/entity/registry.h"
#include "core/ecs/resource/registry.h"
#include "core/ecs/system/manager.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        class Commands : SystemParameter {
            public:
            Commands(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept;
            Commands(const Commands&) = delete;
            Commands(Commands&&) = delete;
            Commands& operator=(const Commands&) = delete;
            Commands& operator=(Commands&&) = delete;

            Entity& spawn() noexcept;
        };
    }  // namespace core::ecs
}  // namespace cobalt