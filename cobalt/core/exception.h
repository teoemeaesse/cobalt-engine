/**
 * @file exception.h
 * @brief Core exception class for handling errors and exceptions in the engine core.
 * @author Tomás Marques
 * @date 07-05-2024
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core {
        class CoreExceptionInterface : public std::runtime_error {
            protected:
            CoreExceptionInterface(const std::string message) : std::runtime_error(message) {}
        };

        template <typename T>
        class CoreException : public CoreExceptionInterface {
            public:
            CoreException(const std::string& message) : CoreExceptionInterface(demangle(typeid(T).name()) + " threw: " + message) {}
            CoreException(const char* message) : CoreExceptionInterface(demangle(typeid(T).name()) + " threw: " + message) {}
        };
    }  // namespace core
}  // namespace cobalt