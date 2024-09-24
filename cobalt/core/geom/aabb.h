/**
 * @file aabb.h
 * @brief An axis-aligned bounding box represents the volume occupied by an object in a space. Can be used for collision detection and spatial
 * partitioning, for example.
 * @author Tomás Marques
 * @date 23-08-2024
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::geom {

        /**
         * @brief An axis-aligned bounding box represents the volume occupied by an object in a space. Can be used for collision detection and spatial
         * partitioning, for example.
         */
        class AABB {
            public:
            /**
             * @brief Creates an empty axis-aligned bounding box.
             */
            AABB() noexcept;
            /**
             * @brief Creates an axis-aligned bounding box.
             * @param min The minimum point of the box.
             * @param max The maximum point of the box.
             */
            AABB(const glm::vec3& min, const glm::vec3& max) noexcept;

            /**
             * @brief Checks if this box intersects with another. Two boxes intersect if they overlap in any way, or touch each other.
             * @param other The other box.
             * @return Whether the boxes intersect.
             */
            bool intersects(const AABB& other) const noexcept;

            /**
             * @brief Checks if this box contains a point.
             * @param point The point.
             * @return Whether the box contains the point.
             */
            bool contains(const glm::vec3& point) const noexcept;

            /**
             * @brief Checks if this box contains another box.
             * @param other The other box.
             * @return Whether the box contains the other box.
             */
            bool contains(const AABB& other) const noexcept;

            /**
             * @brief Expands this box to include another box.
             * @param other The other box.
             */
            void expand(const AABB& other) noexcept;

            /**
             * @brief Combines two boxes into a new box.
             * @param other The other box.
             * @return The resulting box.
             */
            AABB combine(const AABB& other) const noexcept;

            /**
             * @brief Expands this box to include another box.
             * @param other The other box.
             */
            void operator+=(const AABB& other) noexcept;

            /**
             * @brief Combines two boxes into a new box.
             * @param other The other box.
             * @return The resulting box.
             */
            AABB operator+(const AABB& other) const noexcept;

            /**
             * @brief Increases the size of the box by the smallest amount possible (FLT_EPSILON).
             */
            void step() noexcept;

            /**
             * @brief Gets the minimum point of the box.
             * @return The minimum point.
             */
            const glm::vec3& getMin() const noexcept;

            /**
             * @brief Gets the maximum point of the box.
             * @return The maximum point.
             */
            const glm::vec3& getMax() const noexcept;

            /**
             * @brief Gets the size of the box.
             * @return The size.
             */
            const glm::vec3 getSize() const noexcept;

            /**
             * @brief Gets the center of the box.
             * @return The center.
             */
            const glm::vec3 getCenter() const noexcept;

            private:
            glm::vec3 min;  // The minimum point of the box.
            glm::vec3 max;  // The maximum point of the box.
        };
    }  // namespace core::geom
}  // namespace cobalt