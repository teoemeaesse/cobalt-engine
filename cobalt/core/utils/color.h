// Created by tomas on
// 02-12-2023

#pragma once

#include <string>

namespace cobalt {
    namespace core {
        class Color {
            public:
            /**
             * @brief: Default color is black.
             * @return: Color
             */
            Color() noexcept;
            /**
             * @brief: Construct a color from 4 floats.
             * @param r: Red component.
             * @param g: Green component.
             * @param b: Blue component.
             * @param a: Alpha component.
             * @return: Color
             */
            Color(const float r, const float g, const float b, const float a = 1.0f) noexcept;
            /**
             * @brief: Construct a color from 4 unsigned chars.
             * @param r: Red component.
             * @param g: Green component.
             * @param b: Blue component.
             * @param a: Alpha component.
             * @return: Color
             */
            Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 255) noexcept;
            /**
             * @brief: Copy constructor.
             * @param: Color to copy.
             * @return: Color
             */
            Color(const Color& other) noexcept;
            /**
             * @brief: Move constructor. Just copies the values.
             * @param: Color to move.
             * @return: Color
             */
            Color(Color&& other) noexcept;
            /**
             * @brief: Copy assignment.
             * @param: Color to copy.
             * @return: Color
             */
            Color& operator=(const Color& other) noexcept;
            /**
             * @brief: Move assignment. Just copies the values.
             * @param: Color to move.
             * @return: Color
             */
            Color& operator=(Color&& other) noexcept;

            /**
             * @brief: Equality operator.
             * @param other: Color to compare.
             * @return: bool
             */
            bool operator==(const Color& other) const noexcept;
            /**
             * @brief: Inequality operator.
             * @param other: Color to compare.
             * @return: bool
             */
            bool operator!=(const Color& other) const noexcept;

            /**
             * @brief: Get a string representation of the color.
             * @return: std::string
             */
            std::string toString() const noexcept;

            /**
             * @brief: Convert the color to an array of 4 unsigned chars.
             * @param array: Array to fill.
             * @return: void
             */
            void toUChar(unsigned char* array) const;

            float r, g, b, a;
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
    }      // namespace core
}  // namespace cobalt