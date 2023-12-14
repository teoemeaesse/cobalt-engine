//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/gl/definitions.h"
#include "core/input/peripheral.h"


namespace cobalt {
    namespace core {
        enum class KeyboardInputID {
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
            LSHIFT, RSHIFT, LCTRL, RCTRL, LALT, RALT,
            SPACE, ENTER, ESCAPE, TAB, BACKSPACE, INSERT, DELETE,
            RIGHT, LEFT, DOWN, UP,
            COUNT
        };

        class KeyState {
            friend class Keyboard;
            
            public:
            /* Check if the key is currently down.
             * @return: Whether the key is currently down.
             */
            bool isDown() const;
            /* Check if the key has been polled since the last frame.
             * @return: Whether the key has been polled since the last frame.
             */
            bool isPolled() const;

            private:
            bool down = false;      // Whether the key is currently down.
            bool polled = true;     // Whether the key has been polled since the last frame.

            /* Create a new key state.
             * @return: The new key state.
             */
            KeyState();
            /* Destroy the key state.
             */
            ~KeyState() = default;
        };

        class Keyboard : public Peripheral<KeyboardInputID> {
            public:
            /* Create a new keyboard.
             * @return: The new keyboard.
             */
            Keyboard();
            /* Destroy the keyboard.
             */
            ~Keyboard() = default;

            /* Callback for when a key is pressed.
             * @param key: The key that was pressed.
             * @param action: The action that was performed.
             */
            void onKeyPress(const int key, const int action);
            /* Poll the keyboard for events.
             */
            void pollEvents() override;
            /* Clear all events from the keyboard.
             * @param delta: The time since the last frame (in seconds).
             */
            void clearEvents(const float delta) override;

            /* Get the state of a key.
             * @param key: The key to get the state of.
             * @return: The state of the key.
             */
            KeyState& getKey(const KeyboardInputID key);

            private:
            KeyState keyStates[static_cast<size_t>(KeyboardInputID::COUNT)];    // The states of all the keys.
        };
    }
}