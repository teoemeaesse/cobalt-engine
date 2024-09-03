/**
 * @file aabb.cpp
 * @brief An axis-aligned bounding box represents the volume occupied by an object in a space. Can be used for collision detection and spatial
 * partitioning, for example.
 * @author Tomás Marques
 * @date 23-08-2024
 */

#include "core/geom/aabb.h"

namespace cobalt {
    namespace core::geom {
        AABB::AABB() noexcept : min(FLT_MAX), max(FLT_MIN) {}

        AABB::AABB(const glm::vec3& min, const glm::vec3& max) noexcept : min(min), max(max) {}

        bool AABB::intersects(const AABB& other) const noexcept {
            return min.x <= other.max.x && max.x >= other.min.x && min.y <= other.max.y && max.y >= other.min.y && min.z <= other.max.z &&
                   max.z >= other.min.z;
        }

        bool AABB::contains(const glm::vec3& point) const noexcept {
            return point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z;
        }

        void AABB::expand(const AABB& other) noexcept {
            min = glm::min(min, other.min);
            max = glm::max(max, other.max);
        }

        AABB AABB::combine(const AABB& other) const noexcept { return AABB(glm::min(min, other.min), glm::max(max, other.max)); }

        void AABB::operator+=(const AABB& other) noexcept {
            min = glm::min(min, other.min);
            max = glm::max(max, other.max);
        }

        AABB AABB::operator+(const AABB& other) const noexcept { return AABB(glm::min(min, other.min), glm::max(max, other.max)); }

        void AABB::step() noexcept {
            min -= glm::vec3(FLT_EPSILON);
            max += glm::vec3(FLT_EPSILON);
        }

        const glm::vec3& AABB::getMin() const noexcept { return min; }

        const glm::vec3& AABB::getMax() const noexcept { return max; }

        const glm::vec3 AABB::getSize() const noexcept { return max - min; }

        const glm::vec3 AABB::getCenter() const noexcept { return (min + max) / 2.0f; }

        AABB::CompareAxis::CompareAxis(Axis axis) noexcept : axis(axis) {}

        bool AABB::CompareAxis::operator()(const AABB& a, const AABB& b) const noexcept {
            return a.getCenter()[(int)axis] < b.getCenter()[(int)axis];
        }
    }  // namespace core::geom
}  // namespace cobalt