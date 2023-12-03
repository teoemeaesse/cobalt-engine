//
// Created by tomas on 03-12-2023.
//

#include "core/gl/definitions.h"
#include "core/exceptions/input_exception.h"

#include "core/input/mouse.h"


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

        Mouse::Mouse(const float sensitivity) : 
        x(0), y(0), dx(0), dy(0), dsx(0), dsy(0),
        sensitivity(sensitivity) {
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
                buttonStates[static_cast<size_t>(Button::LEFT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                buttonStates[static_cast<size_t>(Button::RIGHT)].down = action == GLFW_PRESS;
            } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                buttonStates[static_cast<size_t>(Button::MIDDLE)].down = action == GLFW_PRESS;
            }
        }

        ButtonState& Mouse::getButton(const Button button) {
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