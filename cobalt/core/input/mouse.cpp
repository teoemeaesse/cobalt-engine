//
// Created by tomas on 03-12-2023.
//

#include "core/input/mouse.h"
#include "core/exceptions/input_exception.h"


namespace cobalt {
    namespace core {
        const std::string Mouse::NAME = "Mouse";

        ButtonState::ButtonState() : down(false), polled(false) {
        }

        bool ButtonState::isDown() const {
            return down;
        }

        bool ButtonState::isPolled() const {
            return polled;
        }

        Mouse::Mouse(const DeviceID id, const float sensitivity) : Peripheral(id),
            sensitivity(sensitivity),
            x(0.0f), y(0.0f),
            dx(0.0f), dy(0.0f),
            dsx(0.0f), dsy(0.0f) {
            for (size_t i = 0; i < static_cast<size_t>(MouseInputID::MIDDLE); i++) {
                buttonStates[i] = ButtonState();
            }
        }

        void Mouse::onMove(const float x, const float y) {
            dx += (x - this->x) * sensitivity;
            dy += (y - this->y) * sensitivity;
            this->x = x;
            this->y = y;
        }

        void Mouse::onScroll(const float dx, const float dy) {
            dsx = dx;
            dsy = dy;
        }

        void Mouse::onButtonPress(const int button, const int action) {
            MouseInputID id = glfwToCobalt(button);
            if (id == MouseInputID::UNKNOWN) {
                throw InvalidInputException<MouseInputID>("Invalid button", button, this);    
            }
            buttonStates[static_cast<size_t>(id)].down = action == GLFW_PRESS;
        }

        void Mouse::queueEvent(const MouseInputID id, const InputValue value) {
            auto it = bindings.find(id);
            if (it != bindings.end()) {
                events.push(it->second.get()->withInput(value));
            }
        }

        void Mouse::pollEvents() {
            // Buttons
            for (size_t i = 0; i < 3; i++) {
                ButtonState &state = buttonStates[i];
                if (state.down) {
                    queueEvent(static_cast<MouseInputID>(i), {state.down, state.polled, 1.0f});
                    if (!state.polled) {
                        state.polled = true;
                    }
                } else if (state.polled) {
                    state.polled = false;
                    queueEvent(static_cast<MouseInputID>(i), {state.down, state.polled, 1.0f});
                }
            }

            // Axes
            if (dx != 0.0f) {
                queueEvent(MouseInputID::AXIS_X, { true, false, dx});
                for (size_t i = 0; i < 3; i++) {
                    if(buttonStates[i].down) {
                        queueEvent(static_cast<MouseInputID>(i + 3), { true, false, dx});
                    }
                }
                dx = 0.0f;
            }
            if (dy != 0.0f) {
                queueEvent(MouseInputID::AXIS_Y, { true, false, dy});
                for (size_t i = 0; i < 3; i++) {
                    if(buttonStates[i].down) {
                        queueEvent(static_cast<MouseInputID>(i + 6), { true, false, dy});
                    }
                }
                dy = 0.0f;
            }

            // Scroll
            if (dsx != 0.0f) {
                queueEvent(MouseInputID::SCROLL_X, { true, false, dsx});
                dsx = 0.0f;
            }
            if (dsy != 0.0f) {
                queueEvent(MouseInputID::SCROLL_Y, { true, false, dsy});
                dsy = 0.0f;
            }
        }

        void Mouse::clearEvents() {
            while (!events.empty()) {
                events.front()->execute();
                events.pop();
            }
        }

        ButtonState& Mouse::getButton(const MouseInputID button) {
            return buttonStates[static_cast<size_t>(button)];
        }

        float Mouse::getX() const {
            return x;
        }

        float Mouse::getY() const {
            return y;
        }

        float Mouse::getDX() const {
            return dx;
        }

        float Mouse::getDY() const {
            return dy;
        }

        float Mouse::getDSX() const {
            return dsx;
        }

        float Mouse::getDSY() const {
            return dsy;
        }

        float Mouse::getSensitivity() const {
            return sensitivity;
        }

        void Mouse::setSensitivity(const float sensitivity) {
            this->sensitivity = sensitivity;
        }


        const static UMap<int, MouseInputID> GLFW_TO_CB = {
            { GLFW_MOUSE_BUTTON_LEFT, MouseInputID::LEFT },
            { GLFW_MOUSE_BUTTON_RIGHT, MouseInputID::RIGHT },
            { GLFW_MOUSE_BUTTON_MIDDLE, MouseInputID::MIDDLE }
        };

        const static UMap<MouseInputID, std::string> CB_TO_STR = {
            { MouseInputID::LEFT, "Left" }, { MouseInputID::RIGHT, "Right" }, { MouseInputID::MIDDLE, "Middle" },
            { MouseInputID::AXIS_X, "X" }, { MouseInputID::AXIS_Y, "Y" },
            { MouseInputID::LEFT_X, "Left X" }, { MouseInputID::LEFT_Y, "Left Y" },
            { MouseInputID::RIGHT_X, "Right X" }, { MouseInputID::RIGHT_Y, "Right Y" },
            { MouseInputID::MIDDLE_X, "Middle X" }, { MouseInputID::MIDDLE_Y, "Middle Y" },
            { MouseInputID::SCROLL_X, "Scroll X" }, { MouseInputID::SCROLL_Y, "Scroll Y" },
            { MouseInputID::COUNT, "Count" }, { MouseInputID::UNKNOWN, "Unknown" }
        };

        const std::string& Mouse::toString() const {
            return NAME;
        }

        const MouseInputID Mouse::glfwToCobalt(const int glfwCode) const {
            auto it = GLFW_TO_CB.find(glfwCode);
            if (it != GLFW_TO_CB.end()) {
                return it->second;
            }
            return MouseInputID::UNKNOWN;
        }

        const int Mouse::cobaltToGlfw(const MouseInputID cobaltCode) const {
            for (const auto& [glfwCode, cobaltCode_] : GLFW_TO_CB) {
                if (cobaltCode_ == cobaltCode) {
                    return glfwCode;
                }
            }
            return GLFW_KEY_UNKNOWN;
        }

        const std::string& Mouse::cobaltToStr(const MouseInputID cobaltCode) const {
            auto it = CB_TO_STR.find(cobaltCode);
            if (it != CB_TO_STR.end()) {
                return it->second;
            }
            return CB_TO_STR.at(MouseInputID::UNKNOWN);
        }
    }
}