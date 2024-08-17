/**
 * @file color.cpp
 * @brief Color class to represent RGBA colors.
 * @author Tomás Marques
 * @date 02-12-2023
 */

#pragma once

#include <glm/glm.hpp>
#include <string>

namespace cobalt {
    namespace core {
        /**
         * @brief Class to represent RGBA colors. The components are floats between 0 and 1.
         */
        class Color {
            public:
            /**
             * @brief Default color is black.
             */
            Color() noexcept;
            /**
             * @brief Construct a color from 4 floats.
             * @param r Red component.
             * @param g Green component.
             * @param b Blue component.
             * @param a Alpha component.
             */
            Color(const float r, const float g, const float b, const float a = 1.0f) noexcept;
            /**
             * @brief Construct a color from 4 unsigned chars.
             * @param r Red component.
             * @param g Green component.
             * @param b Blue component.
             * @param a Alpha component.
             */
            Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 255) noexcept;
            /**
             * @brief Copy constructor.
             * @param Color to copy.
             */
            Color(const Color& other) noexcept;
            /**
             * @brief Move constructor. Just copies the values.
             * @param Color Color to move.
             */
            Color(Color&& other) noexcept;
            /**
             * @brief Copy assignment.
             * @param Color Color to copy.
             * @return Reference to this after copy.
             */
            Color& operator=(const Color& other) noexcept;
            /**
             * @brief Move assignment. Just copies the values.
             * @param Color Color to move.
             * @return Reference to this after move.
             */
            Color& operator=(Color&& other) noexcept;

            /**
             * @brief Equality operator.
             * @param other Color to compare.
             * @return True if the colors are the same, false otherwise.
             */
            bool operator==(const Color& other) const noexcept;
            /**
             * @brief Inequality operator.
             * @param other Color to compare.
             * @return True if the colors are different, false otherwise.
             */
            bool operator!=(const Color& other) const noexcept;

            /**
             * @brief Convert the color to a glm::vec3.
             * @return glm::vec3 representation of the color.
             */
            operator glm::vec3() const noexcept;
            /**
             * @brief Convert the color to a glm::vec4.
             * @return glm::vec4 representation of the color.
             */
            operator glm::vec4() const noexcept;
            /**
             * @brief Convert the color to a string.
             * @return String representation of the color.
             */
            operator std::string() const noexcept;

            /**
             * @brief Get a string representation of the color.
             * @return String representation of the color.
             */
            std::string toString() const noexcept;

            /**
             * @brief Convert the color to an array of 4 unsigned chars.
             * @param array Array to fill.
             */
            void toUChar(unsigned char* array) const;

            float r, g, b, a;  ///< Red, green, blue and alpha components.
        };

        namespace Colors {
            static inline const Color White = Color(1.0f, 1.0f, 1.0f, 1.0f);
            static inline const Color Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
            static inline const Color Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
            static inline const Color Orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
            static inline const Color Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
            static inline const Color Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
            static inline const Color Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
            static inline const Color Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
            static inline const Color Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
            static inline const Color Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
        }  // namespace Colors
    }  // namespace core
}  // namespace cobalt