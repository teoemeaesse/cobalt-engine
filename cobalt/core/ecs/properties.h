/**
 * @file properties.h
 * @brief Properties used by the ECS elements.
 * @author Tomás Marques
 * @date 28-01-2024
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Properties of an entity.
         */
        namespace EntityProperties {
            using ID = uint64;       ///< Entity ID - unique between all entities.
            using Version = uint64;  ///< Entity version - incremented every time an entity with this ID is destroyed.
        };  // namespace EntityProperties

        /**
         * @brief Properties of a component.
         */
        namespace ComponentProperties {
            using Type = uint64;  ///< Component type - unique between different component types.
        };  // namespace ComponentProperties

        /**
         * @brief Properties of a resource.
         */
        namespace ResourceProperties {
            using Type = uint64;  ///< Resource type - unique between different resource types.
        };  // namespace ResourceProperties
    }  // namespace core::ecs
}  // namespace cobalt