// Created by tomas on
// 28-03-2024

#pragma once

#include "core/input/peripheral.h"

namespace cobalt {
    namespace core::input {
        enum class NullInputID { UNKNOWN };

        class NullDevice : public Peripheral<NullInputID> {
            public:
            const static std::string NAME;

            /**
             * @brief: Create a new null peripheral device.
             * @param id: The device id.
             * @return: NullDevice
             */
            NullDevice(const DeviceID id);
            /**
             * @brief: Destroy the null peripheral device.
             * @return: void
             */
            ~NullDevice() = default;

            /**
             * @brief: Get a user-friendly string for the peripheral.
             * @return: The converted string.
             */
            const std::string& toString() const override;
            /**
             * @brief: Convert a GLFW key code to a Cobalt key code.
             * @param glfwCode: The GLFW key code.
             * @return: The Cobalt key code.
             */
            const NullInputID glfwToCobalt(const int glfwCode) const override;
            /**
             * @brief: Convert a Cobalt key code to a GLFW key code.
             * @param cobaltCode: The Cobalt key code.
             * @return: The GLFW key code.
             */
            const int cobaltToGlfw(const NullInputID cobaltCode) const override;
            /**
             * @brief: Convert a Cobalt key code to a user-friendly string.
             * @param cobaltCode: The Cobalt key code.
             * @return: The converted string.
             */
            const std::string& cobaltToStr(const NullInputID cobaltCode) const override;
        };
    }  // namespace core::input
}  // namespace cobalt