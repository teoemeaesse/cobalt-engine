//
// Created by tomas on 30-11-2023.
//

#pragma once

#include <stdexcept>


namespace cobalt {
    namespace core {
        class GLException : public std::runtime_error {
            public:
            GLException(const std::string& message) : std::runtime_error(message) {}
        };
    }
}