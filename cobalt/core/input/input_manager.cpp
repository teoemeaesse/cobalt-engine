//
// Created by tomas on 03-12-2023.
//

#include "core/input/input_manager.h"
#include "core/gfx/render_context.h"


namespace cobalt {
    namespace core {
        void InputManager::pollEvents() {
            glfwPollEvents();
            keyboard.pollEvents();
            mouse.pollEvents();
        }

        void InputManager::clearEvents() {
            keyboard.clearEvents();
            mouse.clearEvents();
        }

        Keyboard& InputManager::getKeyboard() {
            return keyboard;
        }

        Mouse& InputManager::getMouse() {
            return mouse;
        }

        InputManager::InputManager(const float mouseSensitivity) : keyboard(), mouse(mouseSensitivity) {
        }
    }
}