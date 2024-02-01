// Created by tomas on
// 03-12-2023

#pragma once

#include "core/input/peripheral.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::input {
        enum class MouseInputID {
            LEFT,
            RIGHT,
            MIDDLE,
            LEFT_X,
            RIGHT_X,
            MIDDLE_X,
            LEFT_Y,
            RIGHT_Y,
            MIDDLE_Y,
            AXIS_X,
            AXIS_Y,
            SCROLL_X,
            SCROLL_Y,
            COUNT,
            UNKNOWN
        };

        class ButtonState {
            friend class Mouse;

            public:
            /**
             * @brief: Check if the button is currently down.
             * @return: Whether the button is currently down.
             */
            bool isDown() const;
            /**
             * @brief: Check if the button has been polled since the last frame.
             * @return: Whether the button has been polled since the last frame.
             */
            bool isPolled() const;

            private:
            bool down;    // Whether the button is currently down.
            bool polled;  // Whether the button has been polled since the last frame.

            /**
             * @brief: Create a new button.
             * @return: A new button.
             */
            ButtonState();
            /**
             * @brief: Destroy the button.
             */
            ~ButtonState() = default;
        };

        class Mouse : public Peripheral<MouseInputID> {
            public:
            const static std::string NAME;

            /**
             * @brief: Create a new mouse with the given sensitivity.
             * @param id: The device id for the mouse.
             * @param sensitivity: The mouse sensitivity.
             * @return: A new mouse.
             */
            Mouse(const DeviceID id, const float sensitivity);
            /**
             * @brief: Destroy the mouse.
             */
            ~Mouse() = default;

            /**
             * @brief: Callback for when the mouse moves.
             * Interfaces with GLFW.
             * @param x: The new x position.
             * @param y: The new y position.
             * @return: void
             */
            void onMove(const float x, const float y);
            /**
             * @brief: Callback for when the mouse scrolls.
             * Interfaces with GLFW.
             * @param x: The new x scroll.
             * @param y: The new y scroll.
             * @return: void
             */
            void onScroll(const float dx, const float dy);
            /**
             * @brief: Callback for when a mouse button is pressed.
             * Interfaces with GLFW.
             * @param button: The button that was pressed.
             * @param action: The action that was performed.
             * @return: void
             */
            void onButtonPress(const int button, const int action);

            /**
             * @brief: Poll the keyboard for events.
             * @return: void
             */
            void pollEvents() override;
            /**
             * @brief: Clear all events from the keyboard.
             * @return: void
             */
            void clearEvents() override;

            /**
             * @brief: Get the state of a button.
             * @param button: The button to get the state of.
             * @return: The state of the button.
             */
            ButtonState& getButton(const MouseInputID button);
            /**
             * @brief: Get the current x position. Relative to the top left corner of the
             * window's content area.
             * @return: The current x position.
             */
            float getX() const;
            /**
             * @brief: Get the current y position. Relative to the top left corner of the
             * window's content area.
             * @return: The current y position.
             */
            float getY() const;
            /**
             * @brief: Get the delta x position. Relative to the top left corner of the window's
             * content area.
             * @return: The delta x position.
             */
            float getDX() const;
            /**
             * @brief: Get the delta y position. Relative to the top left corner of the window's
             * content area.
             * @return: The delta y position.
             */
            float getDY() const;
            /**
             * @brief: Get the delta x scroll.
             * @return: The delta x scroll.
             */
            float getDSX() const;
            /**
             * @brief: Get the delta y scroll.
             * @return: The delta y scroll.
             */
            float getDSY() const;
            /**
             * @brief: Get the sensitivity.
             * @return: The sensitivity.
             */
            float getSensitivity() const;
            /**
             * @brief: Set the sensitivity.
             * @param sensitivity: The new sensitivity.
             */
            void setSensitivity(const float sensitivity);

            private:
            float x, y;         // Current position. Relative to the top left corner of the window's content area.
            float dx, dy;       // Delta position - difference between the current and last polled position.
            float dsx, dsy;     // Delta scroll - difference between the current and last polled scroll.
            float sensitivity;  // Mouse sensitivity.

            ButtonState buttonStates[3];  // States of the mouse buttons.

            /**
             * @brief: Queue an event.
             * @param id: The id of the event.
             * @param value: The value of the event.
             */
            void queueEvent(const MouseInputID id, const InputValue value);

            public:  // ----- DEBUG -----
            /**
             * @brief: Get a user-friendly string for the peripheral.
             * @return: The converted string.
             */
            const std::string& toString() const override;
            /**
             * @brief: Convert a GLFW key code to a Cobalt key code.
             * @param glfwCode: The GLFW key code.
             * @return: The Cobalt key code.
             */
            const MouseInputID glfwToCobalt(const int glfwCode) const override;
            /**
             * @brief: Convert a Cobalt key code to a GLFW key code.
             * @param cobaltCode: The Cobalt key code.
             * @return: The GLFW key code.
             */
            const int cobaltToGlfw(const MouseInputID cobaltCode) const override;
            /**
             * @brief: Convert a Cobalt key code to a user-friendly string.
             * @param cobaltCode: The Cobalt key code.
             * @return: The converted string.
             */
            const std::string& cobaltToStr(const MouseInputID cobaltCode) const override;
        };
    }  // namespace core::input
}  // namespace cobalt