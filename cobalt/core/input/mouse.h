//
// Created by tomas on 03-12-2023.
//

#pragma once


namespace cobalt {
    namespace core {
        enum class Button {
            LEFT, RIGHT, MIDDLE, COUNT
        };

        class ButtonState {
            friend class Mouse;

            public:
            /* Check if the button is currently down.
             * @return: Whether the button is currently down.
             */
            bool isDown() const;
            /* Check if the button has been polled since the last frame.
             * @return: Whether the button has been polled since the last frame.
             */
            bool isPolled() const;

            private:
            bool down;      // Whether the button is currently down.
            bool polled;    // Whether the button has been polled since the last frame.
            
            /* Create a new button.
             * @return: A new button.
             */
            ButtonState();
            /* Destroy the button.
             */
            ~ButtonState() = default;
        };

        class Mouse {
            public:
            /* Create a new mouse with the given sensitivity.
             * @param sensitivity: The mouse sensitivity.
             * @return: A new mouse.
             */
            Mouse(const float sensitivity);
            /* Destroy the mouse.
             */
            ~Mouse() = default;

            /* Callback for when the mouse moves.
             * Interfaces with GLFW.
             * @param x: The new x position.
             * @param y: The new y position.
             */
            void onMove(const float x, const float y);
            /* Callback for when the mouse scrolls.
             * Interfaces with GLFW.
             * @param x: The new x scroll.
             * @param y: The new y scroll.
             */
            void onScroll(const float dx, const float dy);
            /* Callback for when a mouse button is pressed.
             * Interfaces with GLFW.
             * @param button: The button that was pressed.
             * @param action: The action that was performed.
             */
            void onButtonPress(const int button, const int action);

            /* Get the state of a button.
             * @param button: The button to get the state of.
             * @return: The state of the button.
             */
            ButtonState& getButton(const Button button);

            /* Get the current x position. Relative to the top left corner of the window's content area.
             * @return: The current x position.
             */
            float getX() const;
            /* Get the current y position. Relative to the top left corner of the window's content area.
             * @return: The current y position.
             */
            float getY() const;
            /* Get the delta x position. Relative to the top left corner of the window's content area.
             * @return: The delta x position.
             */
            float getDX() const;
            /* Get the delta y position. Relative to the top left corner of the window's content area.
             * @return: The delta y position.
             */
            float getDY() const;
            /* Get the delta x scroll.
             * @return: The delta x scroll.
             */
            float getDSX() const;
            /* Get the delta y scroll.
             * @return: The delta y scroll.
             */
            float getDSY() const;
            /* Get the sensitivity.
             * @return: The sensitivity.
             */
            float getSensitivity() const;
            /* Set the sensitivity.
             * @param sensitivity: The new sensitivity.
             */
            void setSensitivity(const float sensitivity);

            private:
            float x, y;         // Current position. Relative to the top left corner of the window's content area.
            float dx, dy;       // Delta position - difference between the current and last polled position.
            float dsx, dsy;     // Delta scroll - difference between the current and last polled scroll.
            float sensitivity;  // Mouse sensitivity.

            ButtonState buttonStates[static_cast<size_t>(Button::COUNT)];
        };
    }
}