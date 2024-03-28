// Created by tomas on
// 28-03-2024

#include "core/input/null.h"

namespace cobalt {
    namespace core::input {
        const std::string NullDevice::NAME = "Null";

        NullDevice::NullDevice(const DeviceID id) : Peripheral<NullInputID>(id) {}

        const std::string& NullDevice::toString() const { return NAME; }

        const NullInputID NullDevice::glfwToCobalt(const int glfwCode) const { return NullInputID::UNKNOWN; }

        const int NullDevice::cobaltToGlfw(const NullInputID cobaltCode) const { return GLFW_KEY_UNKNOWN; }

        const std::string& NullDevice::cobaltToStr(const NullInputID cobaltCode) const { return NAME; }
    }  // namespace core::input
}  // namespace cobalt