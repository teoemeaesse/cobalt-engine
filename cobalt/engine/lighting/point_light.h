/**
 * @file point_light.h
 * @brief A point light source that emits light in all directions from a single point in space.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#pragma once

#include "core/ecs/component/component.h"
#include "core/ecs/resource/resource.h"
#include "core/gl/ubo.h"
#include "core/utils/color.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A point light source emits light in all directions from a single point in space. Should be attached to an entity with a transform
         * component.
         */
        class PointLight : public core::ecs::Component {
            private:
            /**
             * @brief Serialized representation of a point light for use in a Buffer.
             */
            struct Serial {
                glm::vec3 position;  ///< World position of the light.
                float intensity;     ///< Intensity of the light.
                glm::vec3 color;     ///< Color of the light.
                float _;             ///< Memory padding

                Serial() noexcept;
                /**
                 * @brief Creates a new Serial representation of a point light.
                 * @param light The point light to serialize.
                 * @param position The world position of the light.
                 */
                Serial(const PointLight& light, const glm::vec3& position) noexcept;
            };

            public:
            /**
             * @brief Creates a new point light.
             * @param intensity The intensity of the light.
             * @param color The color of the light.
             */
            PointLight(float intensity, const core::Color& color) noexcept;
            /**
             * @brief Default destructor.
             */
            ~PointLight() noexcept = default;

            /**
             * @brief A UBO specialization for point lights. This assumes the following shader code:
             *      layout (std140) uniform Light {
             *          LightStruct u_lights[MAX_LIGHTS];
             *          float u_count;
             *      };
             * You should only push the point lights.
             * @tparam length The maximum number of point lights in the buffer.
             */
            template <uint length>
            class UBO : public core::gl::UBO, public core::ecs::Resource {
                public:
                /**
                 * @brief Creates a new UBO for point lights.
                 * @param usage The usage of the buffer.
                 */
                explicit UBO(const core::gl::Usage usage) : core::gl::UBO(usage, length * sizeof(Serial) + sizeof(float)) {}

                virtual void send() override {
                    float count = size / sizeof(Serial);
                    glBufferSubData(GL_UNIFORM_BUFFER, size, sizeof(float), &count);
                }
            };

            private:
            float intensity;    ///< Intensity of the light.
            core::Color color;  ///< Color of the light.
        };
    }  // namespace engine
}  // namespace cobalt
