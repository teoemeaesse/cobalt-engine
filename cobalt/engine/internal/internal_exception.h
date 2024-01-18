//
// Created
// by
// tomas
// on
// 24-12-2023.
//

#pragma once

#include <stdexcept>

namespace cobalt {
    namespace engine {
        class InternalException : public std::runtime_error {
            public:
            InternalException(const std::string& message) : std::runtime_error(message) {}
            InternalException(const char* message) : std::runtime_error(message) {}
        };
    }  // namespace engine
}  // namespace
   // cobalt