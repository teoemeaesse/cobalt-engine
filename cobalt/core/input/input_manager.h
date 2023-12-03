//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/input/keyboard.h"
#include "core/input/mouse.h"


namespace cobalt {
    namespace core {
        class InputManager {
            public:
            /* Create a new input manager.
             * @param mouseSensitivity: The mouse sensitivity.
             * @return: The new input manager.
             */
            InputManager(const float mouseSensitivity = 1.0f);
            /* Destroy the input manager.
             */
            ~InputManager() = default;
            
            private:
            Keyboard keyboard;
            Mouse mouse;
        };
    }
}