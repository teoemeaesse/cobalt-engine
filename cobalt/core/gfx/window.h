// Created by tomas on
// 02-12-2023

#pragma once

#include "core/gl/fbo.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::gfx {
        enum class WindowMode { Windowed, Fullscreen, Borderless };

        /** @brief: Wrapper for GLFW window.
         */
        class Window {
            friend class WindowBuilder;

            public:
            typedef void (*CallbackSetter)();

            /** @brief: Destroys the window.
             */
            ~Window();

            /** @brief: Swap the front and back buffers of the window.
             */
            void swapBuffers() const;
            /** @brief: Switches the mode of the window.
             * VAOs and VBOs are not preserved, so make sure to rebuild your
             * scene after switching the mode of the window.
             * @param mode: The new mode of the window.
             */
            void switchMode(const WindowMode mode);
            /** @brief: Makes the window visible
             */
            void show() const;
            /** @brief: Hides the window.
             */
            void hide() const;
            /** @brief: Clears the screen to the default color.
             */
            void clear();
            /** @brief: Checks if the window should close.
             * @return: Whether or not the window should close.
             */
            bool shouldClose() const;
            /** @brief: Sets the clear color of the window.
             * @param color: The color to clear the screen to.
             */
            void setClearColor(const Color& color);
            /** @brief: Called when the window is resized.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             */
            void onResize(const uint width, const uint height);
            /** @brief: Call to resize the GLFW window to match this window's dimensions.
             */
            void resize();

            /** @brief: Gets the width of the window.
             * @return: The width of the window.
             */
            const uint getWidth() const;
            /** @brief: Gets the height of the window.
             * @return: The height of the window.
             */
            const uint getHeight() const;
            /** @brief: Gets the default framebuffer object of the window.
             * @return: The default framebuffer object of the window.
             */
            gl::FBO& getDefaultFBO();
            /** @brief: Gets whether or not the window is using vsync.
             * @return: Whether or not the window is using vsync.
             */
            const bool isVsync() const;
            /** @brief: Gets the mode of the window.
             * @return: The mode of the window.
             */
            const WindowMode getMode() const;

            /** @brief: Sets the dimensions of the window.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             */
            void setDimensions(const uint width, const uint height);
            /** @brief: Sets whether or not the window is using vsync.
             * @param vsync: Whether or not the window is using vsync.
             */
            void setVsync(const bool vsync);
            /** @brief: Sets the mode of the window.
             * @param mode: The new mode of the window.
             */
            void setMode(const WindowMode mode);
            /** @brief: Sets the title of the window.
             * @param title: The new title of the window.
             */
            void setTitle(const std::string& title);

            private:
            /** @brief: Creates a new window.
             * @param width: The width of the window.
             * @param height: The height of the window.
             * @param title: The title of the window.
             * @param vsync: Whether or not the window should be using vsync.
             * @param mode: The mode of the window.
             * @param resizable: Whether or not the window should be resizable.
             * @param decorated: Whether or not the window should be decorated.
             * @param lockAspectRatio: Whether or not the aspect ratio of the window
             * should be locked.
             * @param callbackSetter: The function to set the callbacks of the window.
             * @return: A new window.
             */
            Window(const uint width, const uint height, const std::string& title, const bool vsync, const WindowMode mode, const bool resizable,
                   const bool decorated, const bool lockAspectRatio, const CallbackSetter callbackSetter);

            uint width,
                height;               // The width and height of the window.
            std::string title;        // The title of the window.
            gl::FBO defaultFBO;       // The default framebuffer object of the window.
            bool vsync;               // Whether or not the window is using vsync.
            bool resizable;           // Whether or not the window is resizable.
            bool decorated;           // Whether or not the window is decorated.
            bool lockAspectRatio;     // Whether or not the aspect ratio of the window is
                                      // locked.
            const float aspectRatio;  // The aspect ratio of the window.
            WindowMode mode;          // The mode of the window.

            const CallbackSetter callbackSetter;  // The function to set the callbacks of
                                                  // the window. It is important to have
                                                  // this for when the window is recreated.

            /** @brief: Initializes the window.
             * Called on construction and after changing window hints.
             */
            void init();
        };

        /** @brief: Builder for windows.
         */
        class WindowBuilder {
            public:
            /** @brief: Creates a new window builder with default values.
             * @return: A new window builder.
             */
            WindowBuilder();
            /** @brief: Destroys the window builder.
             */
            ~WindowBuilder() = default;

            /** @brief: Sets the width of the window.
             * @param width: The width of the window.
             * @return: The window builder.
             */
            WindowBuilder& setWidth(const uint width);
            /** @brief: Sets the height of the window.
             * @param height: The height of the window.
             * @return: The window builder.
             */
            WindowBuilder& setHeight(const uint height);
            /** @brief: Sets the title of the window.
             * @param title: The title of the window.
             * @return: The window builder.
             */
            WindowBuilder& setTitle(const std::string& title);
            /** @brief: Sets whether or not the window is using vsync.
             * @param vsync: Whether or not the window is using vsync.
             * @return: The window builder.
             */
            WindowBuilder& setVsync(const bool vsync);
            /** @brief: Sets the mode of the window.
             * @param mode: The mode of the window.
             * @return: The window builder.
             */
            WindowBuilder& setMode(const WindowMode mode);
            /** @brief: Sets whether or not the window is resizable.
             * @param resizable: Whether or not the window is resizable.
             * @return: The window builder.
             */
            WindowBuilder& setResizable(const bool resizable);
            /** @brief: Sets whether or not the window is decorated.
             * @param decorated: Whether or not the window is decorated.
             * @return: The window builder.
             */
            WindowBuilder& setDecorated(const bool decorated);
            /** @brief: Locks the aspect ratio of the window.
             * @param lockAspectRatio: The aspect ratio of the window.
             * @return: The window builder.
             */
            WindowBuilder& setLockAspectRatio(const bool lockAspectRatio);
            /** @brief: Sets the callbacks setter (sorry) of the window.
             * @param callbackSetter: The function to set the callbacks of the window.
             * @return: The window builder.
             */
            WindowBuilder& setCallbackSetter(Window::CallbackSetter callbackSetter);

            /** @brief: Builds the window.
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
            Window::CallbackSetter callbackSetter;
        };
    }  // namespace core::gfx
}  // namespace cobalt