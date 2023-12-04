//
// Created by tomas on 03-12-2023.
//

#include "core/input/mouse.h"
#include "core/exceptions/input_exception.h"


namespace cobalt {
    namespace core {
        ButtonState::ButtonState() : down(false), polled(true) {
        }

        bool ButtonState::isDown() const {
            return down;
        }

        bool ButtonState::isPolled() const {
            return polled;
        }

        Mouse::Mouse(const float sensitivity) : sensitivity(sensitivity), x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), dsx(0.0f), dsy(0.0f) {
            for (size_t i = 0; i < static_cast<size_t>(ButtonID::COUNT); i++) {
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
                buttonStates[static_cast<size_t>(ButtonID::LEFT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                buttonStates[static_cast<size_t>(ButtonID::RIGHT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                buttonStates[static_cast<size_t>(ButtonID::MIDDLE)].down = action == GLFW_PRESS;
            }
        }

        void Mouse::pollEvents() {
            // TODO: add to queue
        }

        void Mouse::clearEvents() {
            while (!events.isEmpty()) {
                events.dequeue()->execute({ false, false, 0.0f }); // TODO: use actual values from the state
            }
        }

        ButtonState& Mouse::getButton(const ButtonID button) {
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