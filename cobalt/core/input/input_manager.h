//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/input/input_command.h"
#include "core/input/keyboard.h"
#include "core/input/mouse.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        /* The input manager. Handles all input from peripherals such as the keyboard and mouse.
         * It then dispatches events to the appropriate listeners.
         */
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

            /* Poll all events from the peripherals.
             */
            void pollEvents();
            /* Clear all events from the peripherals.
             */
            void clearEvents();

            /* Get the keyboard.
             * @return: The keyboard.
             */
            Keyboard& getKeyboard();
            /* Get the mouse.
             * @return: The mouse.
             */
            Mouse& getMouse();

            private:
            Keyboard keyboard;          // The keyboard.
            Mouse mouse;                // The mouse.
        };
    }
}