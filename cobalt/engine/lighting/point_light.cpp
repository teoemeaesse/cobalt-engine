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

        PointLight::UBO::UBO(const core::gl::Usage usage) : core::gl::UBO(usage, 32 * sizeof(Serial) + sizeof(float)) {}

        void PointLight::UBO::send() {
            float count = (capacity - sizeof(float)) / sizeof(Serial);
            glBufferSubData(GL_UNIFORM_BUFFER, 32 * sizeof(Serial), sizeof(float), (void*)&count);
            size = 32 * sizeof(Serial) + sizeof(float);
        }
    }  // namespace engine
}  // namespace cobalt