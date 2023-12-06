//
// Created by tomas on 02-12-2023.
//

#pragma once

#include "core/utils/types.h"
#include "core/gl/fbo.h"
#include "core/gfx/color.h"


namespace cobalt {
    namespace core {
        enum class WindowMode {
            Windowed,
            Fullscreen,
            Borderless
        };

        /* Wrapper for GLFW window.
         */
        class Window {
            friend class WindowBuilder;

            public:
            /* Destroys the window.
             */
            ~Window();

            /* Swap the front and back buffers of the window.
             */
            void swapBuffers() const;
            /* Switches the mode of the window.
             * @param mode: The new mode of the window.
             */
            void switchMode(const WindowMode mode);
            /* Makes the window visible
             */
            void show() const;
            /* Hides the window.
             */
            void hide() const;
            /* Clears the screen to the default color.
             */
            void clear();
            /* Checks if the window should close.
             * @return: Whether or not the window should close.
             */
            bool shouldClose() const;
            /* Sets the clear color of the window.
             * @param color: The color to clear the screen to.
             */
            void setClearColor(const Color& color);
            /* Called when the window is resized.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             */
            void onResize(const uint width, const uint height);

            private:
            /* Creates a new window.
             * @param width: The width of the window.
             * @param height: The height of the window.
             * @param title: The title of the window.
             * @param vsync: Whether or not the window should be using vsync.
             * @param mode: The mode of the window.
             * @param resizable: Whether or not the window should be resizable.
             * @param decorated: Whether or not the window should be decorated.
             * @param lockAspectRatio: Whether or not the aspect ratio of the window should be locked.
             * @return: A new window.
             */
            Window(
                const uint width,
                const uint height,
                const std::string& title,
                const bool vsync,
                const WindowMode mode,
                const bool resizable,
                const bool decorated,
                const bool lockAspectRatio
            );

            uint width, height;         // The width and height of the window.
            std::string title;          // The title of the window.
            DefaultFBO defaultFBO;      // The default framebuffer object of the window.
            bool vsync;                 // Whether or not the window is using vsync.
            bool resizable;             // Whether or not the window is resizable.
            bool decorated;             // Whether or not the window is decorated.
            bool lockAspectRatio;       // Whether or not the aspect ratio of the window is locked.
            const float aspectRatio;    // The aspect ratio of the window.
            WindowMode mode;            // The mode of the window.
        
            /* Initializes the window.
             * Called on construction and after changing window hints.
             */
            void init();
        };

        /* Builder for windows.
         */
        class WindowBuilder {
            public:
            /* Creates a new window builder with default values.
             * @return: A new window builder.
             */
            WindowBuilder();
            /* Destroys the window builder.
             */
            ~WindowBuilder() = default;

            /* Sets the width of the window.
             * @param width: The width of the window.
             * @return: The window builder.
             */
            WindowBuilder& setWidth(const uint width);
            /* Sets the height of the window.
             * @param height: The height of the window.
             * @return: The window builder.
             */
            WindowBuilder& setHeight(const uint height);
            /* Sets the title of the window.
             * @param title: The title of the window.
             * @return: The window builder.
             */
            WindowBuilder& setTitle(const std::string& title);
            /* Sets whether or not the window is using vsync.
             * @param vsync: Whether or not the window is using vsync.
             * @return: The window builder.
             */
            WindowBuilder& setVsync(const bool vsync);
            /* Sets the mode of the window.
             * @param mode: The mode of the window.
             * @return: The window builder.
             */
            WindowBuilder& setMode(const WindowMode mode);
            /* Sets whether or not the window is resizable.
             * @param resizable: Whether or not the window is resizable.
             * @return: The window builder.
             */
            WindowBuilder& setResizable(const bool resizable);
            /* Sets whether or not the window is decorated.
             * @param decorated: Whether or not the window is decorated.
             * @return: The window builder.
             */
            WindowBuilder& setDecorated(const bool decorated);
            /* Locks the aspect ratio of the window.
             * @param lockAspectRatio: The aspect ratio of the window.
             * @return: The window builder.
             */
            WindowBuilder& setLockAspectRatio(const bool lockAspectRatio);

            /* Builds the window.
             * @return: The window.
             */
            Window build() const;

            private:
            uint width, height;
            std::string title;
            bool vsync;
            WindowMode mode;
            bool resizable;
            bool decorated;
            bool lockAspectRatio;
        };
    }
}