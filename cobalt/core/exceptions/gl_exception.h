//
// Created
// by
// tomas
// on
// 30-11-2023.
//

#pragma once

#include <stdexcept>

namespace cobalt {
    namespace core::gl {
        class GLException : public std::runtime_error {
            public:
            GLException(const std::string& message) : std::runtime_error(message) {}
            GLException(const char* message) : std::runtime_error(message) {}
        };
    }  // namespace core::gl
}  // namespace cobalt