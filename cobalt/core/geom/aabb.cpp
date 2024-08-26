/**
 * @file aabb.cpp
 * @brief An axis-aligned bounding box. Can be used for collision detection and spatial partitioning.
 * @author Tomás Marques
 * @date 23-08-2024
 */

#include "core/geom/aabb.h"

namespace cobalt {
    namespace core::geom {
        AABB2::AABB2(const glm::vec2& min, const glm::vec2& max) noexcept : min(min), max(max) {}

        bool AABB2::intersects(const AABB2& other) const noexcept {
            return min.x <= other.max.x && max.x >= other.min.x && min.y <= other.max.y && max.y >= other.min.y;
        }

        bool AABB2::contains(const glm::vec2& point) const noexcept {
            return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y;
        }

        const glm::vec2& AABB2::getMin() const noexcept { return min; }

        const glm::vec2& AABB2::getMax() const noexcept { return max; }

        AABB3::AABB3(const glm::vec3& min, const glm::vec3& max) noexcept : min(min), max(max) {}

        bool AABB3::intersects(const AABB3& other) const noexcept {
            return min.x <= other.max.x && max.x >= other.min.x && min.y <= other.max.y && max.y >= other.min.y && min.z <= other.max.z &&
                   max.z >= other.min.z;
        }

        bool AABB3::contains(const glm::vec3& point) const noexcept {
            return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
        }

        const glm::vec3& AABB3::getMin() const noexcept { return min; }

        const glm::vec3& AABB3::getMax() const noexcept { return max; }
    }  // namespace core::geom
}  // namespace cobalt