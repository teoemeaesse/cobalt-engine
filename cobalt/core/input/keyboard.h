//
// Created by tomas on 03-12-2023.
//

#pragma once

#include "core/pch.h"
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
            /** Check if the key is currently down.
             * @return: Whether the key is currently down.
             */
            bool isDown() const;
            /** Check if the key has been polled since the last frame.
             * @return: Whether the key has been polled since the last frame.
             */
            bool isPolled() const;

            private:
            bool down = false;      // Whether the key is currently down.
            bool polled = true;     // Whether the key has been polled since the last frame.

            /** Create a new key state.
             * @return: The new key state.
             */
            KeyState();
            /** Destroy the key state.
             */
            ~KeyState() = default;
        };

        class Keyboard : public Peripheral<KeyboardInputID> {
            public:
            /** Create a new keyboard.
             * @return: The new keyboard.
             */
            Keyboard();
            /** Destroy the keyboard.
             */
            ~Keyboard() = default;

            /** Callback for when a key is pressed.
             * @param key: The key (glfw) that was pressed.
             * @param action: The action (glfw) that was performed.
             */
            void onKeyPress(const int key, const int action);
            /** Poll the keyboard for events.
             * This generates peripheral events for all keys
             * that are currently down or just released.
             */
            void pollEvents() override;
            /** Clear all events from the keyboard.
             * Executes all pending input events.
             */
            void clearEvents() override;

            /** Get the state of a key.
             * @param key: The key to get the state of.
             * @return: The state of the key.
             */
            KeyState& getKey(const KeyboardInputID key);

            private:
            KeyState keyStates[static_cast<size_t>(KeyboardInputID::COUNT)];    // The states of all the keys.



            public: // ----- DEBUG -----
            /** Convert a GLFW key to a Cobalt key.
             * Mostly for internal use. Use the KeyboardInputID enum instead.
             * @param key: The GLFW key code.
             * @return: The Cobalt key code.
             */
            static const KeyboardInputID glfwToCobalt(const int glfwKey);
            /** Convert a Cobalt key to a GLFW key.
             * Mostly for testing. Use the KeyboardInputID enum instead.
             * @param key: The Cobalt key code.
             * @return: The GLFW key code.
             */
            static const int cobaltToGlfw(const KeyboardInputID cobaltKey);
        };
    }
}