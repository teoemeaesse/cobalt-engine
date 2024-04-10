// Created by tomas on
// 28-01-2024

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        namespace EntityProperties {
            using ID = uint64;       // Entity ID - unique between all entities.
            using Version = uint64;  // Entity version - incremented every time an entity with this ID is destroyed.
        };  // namespace EntityProperties

        namespace ComponentProperties {
            using Type = uint64;  // Component type - unique between different component types.
        };  // namespace ComponentProperties

        namespace ResourceProperties {
            using Type = uint64;  // Resource type - unique between different resource types.
        };  // namespace ResourceProperties
    }  // namespace core::ecs
}  // namespace cobalt