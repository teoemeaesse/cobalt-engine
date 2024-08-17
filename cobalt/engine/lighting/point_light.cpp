/**
 * @file point_light.cpp
 * @brief A point light source that emits light in all directions from a single point in space.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#include "engine/lighting/point_light.h"

namespace cobalt {
    namespace engine {
        PointLight::Serial::Serial(const PointLight& light, const glm::vec3& position) noexcept
            : intensity(light.intensity), color(light.color), position(position), _(0.0f) {}

        PointLight::PointLight(float intensity, const core::Color& color) noexcept : intensity(intensity), color(color) {}
    }  // namespace engine
}  // namespace cobalt