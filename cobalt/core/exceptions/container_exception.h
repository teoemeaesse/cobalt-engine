//
// Created by tomas on 03-12-2023.
//

#pragma once

#include <stdexcept>


namespace cobalt {
    namespace core {
        class ContainerException : public std::runtime_error {
            public:
            ContainerException(const std::string& message) : std::runtime_error(message) {}
        };
    }
}