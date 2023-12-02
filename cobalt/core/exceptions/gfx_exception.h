//
// Created by tomas on 02-12-2023.
//

#pragma once

#include <stdexcept>


namespace cobalt {
    namespace core {
        class GFXException : public std::runtime_error {
            public:
            GFXException(const std::string& message) : std::runtime_error(message) {}
        };
    }
}