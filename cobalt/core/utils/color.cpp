/**
 * @file color.cpp
 * @brief Color class to represent RGBA colors.
 * @author Tomás Marques
 * @date 01-03-2024
 */

#include "core/utils/color.h"

#include <sstream>

namespace cobalt {
    namespace core {
        Color::Color() noexcept : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

        Color::Color(const float r, const float g, const float b, const float a) noexcept : r(r), g(g), b(b), a(a) {}

        Color::Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) noexcept
            : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

        Color::Color(const Color& other) noexcept : r(other.r), g(other.g), b(other.b), a(other.a) {}

        Color::Color(Color&& other) noexcept : r(other.r), g(other.g), b(other.b), a(other.a) {}

        Color& Color::operator=(const Color& other) noexcept {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            return *this;
        }

        Color& Color::operator=(Color&& other) noexcept {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            return *this;
        }

        bool Color::operator==(const Color& other) const noexcept { return r == other.r && g == other.g && b == other.b && a == other.a; }

        bool Color::operator!=(const Color& other) const noexcept { return !(*this == other); }

        Color::operator glm::vec3() const noexcept { return glm::vec3(r, g, b); }

        Color::operator glm::vec4() const noexcept { return glm::vec4(r, g, b, a); }

        Color::operator std::string() const noexcept { return toString(); }

        std::string Color::toString() const noexcept {
            std::stringstream ss;
            ss << "CB_Color(" << r << ", " << g << ", " << b << ", " << a << ")";
            return ss.str();
        }

        void Color::toUChar(unsigned char* array) const {
            if (array == nullptr) return;
            array[0] = static_cast<unsigned char>(r * 255);
            array[1] = static_cast<unsigned char>(g * 255);
            array[2] = static_cast<unsigned char>(b * 255);
            array[3] = static_cast<unsigned char>(a * 255);
        }
    }  // namespace core
}  // namespace cobalt