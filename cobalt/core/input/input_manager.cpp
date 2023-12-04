//
// Created by tomas on 03-12-2023.
//

#include "core/input/input_manager.h"
#include "core/gfx/render_context.h"



#include "core/utils/log.h"




namespace cobalt {
    namespace core {
        static void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            InputManager* inputManager = static_cast<InputManager*>(RenderContext::getUserPointer());
            CB_CORE_ERROR("Key: {0}, scancode: {1}, action: {2}, mods: {3}", key, scancode, action, mods);
            inputManager->getKeyboard().onKeyPress(key, action);
        }

        static void onMouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
            InputManager* inputManager = static_cast<InputManager*>(RenderContext::getUserPointer());
            inputManager->getMouse().onMove((float) xpos, (float) ypos);
        }

        static void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
            InputManager* inputManager = static_cast<InputManager*>(RenderContext::getUserPointer());
            inputManager->getMouse().onButtonPress(button, action);
        }

        static void onMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
            InputManager* inputManager = static_cast<InputManager*>(RenderContext::getUserPointer());
            inputManager->getMouse().onScroll((float) xoffset, (float) yoffset);
        }

        void InputManager::pollEvents() {
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
            RenderContext::setKeyCallback(onKeyCallback);
        }
    }
}