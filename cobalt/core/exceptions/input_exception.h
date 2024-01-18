//
// Created
// by
// tomas
// on
// 30-11-2023.
//

#pragma once

#include <stdexcept>

#include "core/input/peripheral.h"

namespace cobalt {
    namespace core::input {
        template <typename T>
        class InvalidInputException : public std::runtime_error {
            public:
            /** @brief: Create a new input exception.
             * @param error: Brief description of the error.
             * @param cobaltCode: The input that caused the error.
             * @param peripheral: The peripheral that caused the error.
             * @return: The new input exception.
             */
            InvalidInputException(const std::string& error, const T cobaltCode, const Peripheral<T>* peripheral)
                : std::runtime_error(error),
                  message(error + " (by " + peripheral->toString() + " with cobalt input: " + peripheral->cobaltToStr(cobaltCode) + ")"),
                  cobaltCode(cobaltCode),
                  peripheral(peripheral) {}
            /** @brief: Create a new input exception.
             * @param error: Brief description of the error.
             * @param glfwCode: The glfw code that caused the error.
             * @param peripheral: The peripheral that caused the error.
             * @return: The new input exception.
             */
            InvalidInputException(const std::string& error, const int glfwCode, const Peripheral<T>* peripheral)
                : std::runtime_error(error),
                  message(error + " (by " + peripheral->toString() + " with glfw input: " + std::to_string(glfwCode) + ")"),
                  cobaltCode(peripheral->glfwToCobalt(glfwCode)),
                  peripheral(peripheral) {}
            ~InvalidInputException() = default;

            /** @brief: Get the composed error message.
             * @return: The error message.
             */
            virtual const char* what() const throw() override { return message.c_str(); }

            private:
            std::string message;                         // The error message.
            const Opt<T> cobaltCode;                     // The input that caused the error.
            const Opt<const Peripheral<T>*> peripheral;  // The peripheral that caused the error.
        };

        class PeripheralNotFoundException : public std::runtime_error {
            public:
            /** @brief: Create a new peripheral not found exception.
             * @param peripheral: The peripheral that was not found.
             * @return: The new peripheral not found exception.
             */
            PeripheralNotFoundException(const std::string& peripheral) : std::runtime_error("Peripheral not found: " + peripheral) {}
            /** @brief: Create a new peripheral not found exception.
             * @param id: The peripheral's device id that was not found.
             * @return: The new peripheral not found exception.
             */
            PeripheralNotFoundException(const DeviceID id) : std::runtime_error("Peripheral not found for DID: " + std::to_string(id)) {}
            ~PeripheralNotFoundException() = default;
        };
    }  // namespace core::input
}  // namespace cobalt