/**
 * @file point_light.h
 * @brief A point light source that emits light in all directions from a single point in space.
 * @author Tomás Marques
 * @date 16-05-2024
 */

#pragma once

#include "core/core.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A point light source emits light in all directions from a single point in space. Should be attached to an entity with a transform
         * component.
         */
        class PointLight : public core::ecs::Component {
            public:
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
             *          vec3 padding;
             *      };
             * You should only push in point lights.
             */
            class UBO : public core::gl::UBO, public core::ecs::Resource {
                public:
                /**
                 * @brief Creates a new UBO for point lights.
                 * @param usage The usage of the buffer.
                 */
                explicit UBO(const core::gl::Usage usage);

                /**
                 * @brief Sends the point light count to the buffer.
                 */
                virtual void send() override;
            };

            private:
            float intensity;    ///< Intensity of the light.
            core::Color color;  ///< Color of the light.
        };
    }  // namespace engine
}  // namespace cobalt
