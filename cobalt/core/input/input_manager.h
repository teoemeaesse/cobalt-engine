//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/input/keyboard.h"
#include "core/input/mouse.h"
#include "core/containers/queue.h"


namespace cobalt {
    namespace core {
        class InputEvent {
            public:
            enum class Type {
                KEYBOARD,
                MOUSE
            };

            InputEvent(const Type type) : type(type) {}
            virtual ~InputEvent() = default;

            const Type type;
        };

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

            /* Polls the input manager for the next event.
             * @return: The next event or nullptr if there are no events
             */
            InputEvent* poll();
            
            private:
            Keyboard keyboard;          // The keyboard.
            Mouse mouse;                // The mouse.
            Queue<InputEvent*> events;  // The events queue.
        };
    }
}