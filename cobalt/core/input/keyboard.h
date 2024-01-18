//
// Created
// by
// tomas
// on
// 03-12-2023.
//

#pragma once

#include "core/input/peripheral.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::input {
        enum class KeyboardInputID {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            N0,
            N1,
            N2,
            N3,
            N4,
            N5,
            N6,
            N7,
            N8,
            N9,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24,
            F25,
            LSHIFT,
            RSHIFT,
            LCTRL,
            RCTRL,
            LALT,
            RALT,
            SPACE,
            ENTER,
            ESCAPE,
            TAB,
            BACKSPACE,
            INSERT,
            DELETE,
            RIGHT,
            LEFT,
            DOWN,
            UP,
            COUNT,
            UNKNOWN
        };

        class KeyState {
            friend class Keyboard;

            public:
            /** @brief: Check if the key is currently down.
             * @return: Whether the key is currently down.
             */
            bool isDown() const;
            /** @brief: Check if the key has been polled since the last frame.
             * @return: Whether the key has been polled since the last frame.
             */
            bool isPolled() const;

            private:
            bool down = false;   // Whether the key is currently down.
            bool polled = true;  // Whether the key has been polled since the last frame.

            /** @brief: Create a new key state.
             * @return: The new key state.
             */
            KeyState();
            /** @brief: Destroy the key state.
             */
            ~KeyState() = default;
        };

        class Keyboard : public Peripheral<KeyboardInputID> {
            public:
            const static std::string NAME;

            /** @brief: Create a new keyboard.
             * @param id: The device id for the keyboard.
             * @return: The new keyboard.
             */
            Keyboard(const DeviceID id);
            /** @brief: Destroy the keyboard.
             */
            ~Keyboard() = default;

            /** @brief: Callback for when a key is pressed.
             * @param key: The key (glfw) that was pressed.
             * @param action: The action (glfw) that was performed.
             */
            void onKeyPress(const int key, const int action);
            /** @brief: Poll the keyboard for events.
             * This generates peripheral events for all keys
             * that are currently down or just released.
             */
            void pollEvents() override;
            /** @brief: Clear all events from the keyboard.
             * Executes all pending input events.
             */
            void clearEvents() override;

            /** @brief: Get the state of a key.
             * @param key: The key to get the state of.
             * @return: The state of the key.
             */
            KeyState& getKey(const KeyboardInputID key);

            private:
            KeyState keyStates[static_cast<size_t>(KeyboardInputID::COUNT)];  // The states of all the keys.

            public:  // ----- DEBUG -----
            /** @brief: Get a user-friendly string for the peripheral.
             * @return: The converted string.
             */
            const std::string& toString() const override;
            /** @brief: Convert a GLFW key code to a Cobalt key code.
             * @param glfwCode: The GLFW key code.
             * @return: The Cobalt key code.
             */
            const KeyboardInputID glfwToCobalt(const int glfwCode) const override;
            /** @brief: Convert a Cobalt key code to a GLFW key code.
             * @param cobaltCode: The Cobalt key code.
             * @return: The GLFW key code.
             */
            const int cobaltToGlfw(const KeyboardInputID cobaltCode) const override;
            /** @brief: Convert a Cobalt key code to a user-friendly string.
             * @param cobaltCode: The Cobalt key code.
             * @return: The converted string.
             */
            const std::string& cobaltToStr(const KeyboardInputID cobaltCode) const override;
        };
    }  // namespace core
} // namespace cobalt