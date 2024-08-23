/**
 * @file aabb.h
 * @brief A 2D and 3D axis-aligned bounding box. Can be used for collision detection and spatial partitioning.
 * @author Tomás Marques
 * @date 23-08-2024
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::geom {
        /**
         * @brief A 2D axis-aligned bounding box.
         */
        class AABB2 {
            public:
            /**
             * @brief Create a 2D axis-aligned bounding box.
             * @param min The minimum point of the box.
             * @param max The maximum point of the box.
             */
            AABB2(const glm::vec2& min, const glm::vec2& max);

            /**
             * @brief Check if this box intersects with another.
             * @param other The other box.
             * @return Whether the boxes intersect.
             */
            bool intersects(const AABB2& other) const;

            /**
             * @brief Check if this box contains a point.
             * @param point The point.
             * @return Whether the box contains the point.
             */
            bool contains(const glm::vec2& point) const;

            /**
             * @brief Get the minimum point of the box.
             * @return The minimum point.
             */
            const glm::vec2& getMin() const;

            /**
             * @brief Get the maximum point of the box.
             * @return The maximum point.
             */
            const glm::vec2& getMax() const;

            private:
            glm::vec2 min;  // The minimum point of the box.
            glm::vec2 max;  // The maximum point of the box.
        };

        /**
         * @brief A 3D axis-aligned bounding box.
         */
        class AABB3 {
            public:
            /**
             * @brief Create a 3D axis-aligned bounding box.
             * @param min The minimum point of the box.
             * @param max The maximum point of the box.
             */
            AABB3(const glm::vec3& min, const glm::vec3& max);

            /**
             * @brief Check if this box intersects with another.
             * @param other The other box.
             * @return Whether the boxes intersect.
             */
            bool intersects(const AABB3& other) const;

            /**
             * @brief Check if this box contains a point.
             * @param point The point.
             * @return Whether the box contains the point.
             */
            bool contains(const glm::vec3& point) const;

            /**
             * @brief Get the minimum point of the box.
             * @return The minimum point.
             */
            const glm::vec3& getMin() const;

            /**
             * @brief Get the maximum point of the box.
             * @return The maximum point.
             */
            const glm::vec3& getMax() const;

            private:
            glm::vec3 min;  // The minimum point of the box.
            glm::vec3 max;  // The maximum point of the box.
        };
    }  // namespace core::geom
}  // namespace cobalt