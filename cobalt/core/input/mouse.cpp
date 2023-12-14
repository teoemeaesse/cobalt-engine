//
// Created by tomas on 03-12-2023.
//

#include "core/input/mouse.h"
#include "core/exceptions/input_exception.h"


namespace cobalt {
    namespace core {
        ButtonState::ButtonState() : down(false), polled(false) {
        }

        bool ButtonState::isDown() const {
            return down;
        }

        bool ButtonState::isPolled() const {
            return polled;
        }

        Mouse::Mouse(const float sensitivity) : Peripheral(), sensitivity(sensitivity), x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), dsx(0.0f), dsy(0.0f) {
            for (size_t i = 0; i < static_cast<size_t>(MouseInputID::COUNT); i++) {
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
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                buttonStates[static_cast<size_t>(MouseInputID::LEFT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                buttonStates[static_cast<size_t>(MouseInputID::RIGHT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                buttonStates[static_cast<size_t>(MouseInputID::MIDDLE)].down = action == GLFW_PRESS;
            }
        }

        void Mouse::queueEvent(const MouseInputID id, const InputValue value) {
            auto it = bindings.find(id);
            if (it != bindings.end()) {
                events.enqueue(it->second.get()->withInput(value));
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
            while (!events.isEmpty()) {
                events.dequeue()->execute();
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
    }
}