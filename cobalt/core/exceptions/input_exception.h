//
// Created by tomas on 30-11-2023.
//

#pragma once

#include <stdexcept>


namespace cobalt {
    namespace core {
        class InputException : public std::runtime_error {
            public:
            InputException(const std::string& message) : std::runtime_error(message) {}
            InputException(const const char* message) : std::runtime_error(message) {}
        };
    }
}