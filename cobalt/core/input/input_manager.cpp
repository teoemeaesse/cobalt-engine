//
// Created by tomas on 03-12-2023.
//

#include "core/input/input_manager.h"


namespace cobalt {
    namespace core {
        InputManager::InputManager(const float mouseSensitivity) : keyboard(), mouse(mouseSensitivity) {
        }
    }
}