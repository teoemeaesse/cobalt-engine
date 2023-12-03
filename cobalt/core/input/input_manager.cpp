//
// Created by tomas on 03-12-2023.
//

#include "core/input/input_manager.h"
#include "core/gfx/render_context.h"


namespace cobalt {
    namespace core {
        static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            InputManager* inputManager = static_cast<InputManager*>(RenderContext::getUserPointer());
            // TODO
        }

        InputManager::InputManager(const float mouseSensitivity) : keyboard(), mouse(mouseSensitivity) {
        }
    }
}