// Created by tomas on
// 02-12-2023

#pragma once

#include <stdexcept>

namespace cobalt {
    namespace core::gfx {
        class GFXException : public std::runtime_error {
            public:
            GFXException(const std::string& message) : std::runtime_error(message) {}
            GFXException(const char* message) : std::runtime_error(message) {}
        };
    }  // namespace core::gfx
}  // namespace cobalt