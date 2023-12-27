//
// Created by tomas on 30-11-2023.
//

#pragma once

#include <stdexcept>

#include "core/input/peripheral.h"


namespace cobalt {
    namespace core {
        template <typename T>
        class InputException : public std::runtime_error {
            public:
            /** Create a new input exception.
             * @param error: Brief description of the error.
             * @param cobaltCode: The input that caused the error.
             * @param peripheral: The peripheral that caused the error.
             * @return: The new input exception.
             */
            InputException(const std::string& error,
                           const T cobaltCode,
                           const Peripheral<T>& peripheral) : std::runtime_error(error),
                message(error + " (by " + peripheral.toString() + " with cobalt input: " + peripheral.cobaltToStr(cobaltCode) + ")"),
                cobaltCode(cobaltCode),
                peripheral(peripheral) {
            }
            /** Create a new input exception.
             * @param error: Brief description of the error.
             * @param glfwCode: The glfw code that caused the error.
             * @param peripheral: The peripheral that caused the error.
             * @return: The new input exception.
             */
            InputException(const std::string& error,
                           const int glfwCode,
                           const Peripheral<T>& peripheral) : std::runtime_error(error),
                message(error + " (by " + peripheral.toString() + " with glfw input: " + std::to_string(glfwCode) + ")"),
                cobaltCode(peripheral.glfwToCobalt(glfwCode)),
                peripheral(peripheral) {
            }
            ~InputException() = default;
     
            /** Get the composed error message.
             * @return: The error message.
             */
            virtual const char* what() const throw() override {
                return message.c_str();
            }

            private:
            std::string message;                // The error message.
            const T cobaltCode;                 // The input that caused the error. 
            const Peripheral<T>& peripheral;    // The peripheral that caused the error.
        };
    }
}