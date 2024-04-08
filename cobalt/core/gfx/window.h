// Created by tomas on
// 02-12-2023

#pragma once

#include "core/gl/fbo.h"
#include "core/input/input_manager.h"

namespace cobalt {
    namespace core::gfx {
        enum class WindowMode { Windowed, Fullscreen, Borderless };

        class WindowProperties;

        /**
         * @brief: Wrapper for GLFW window.
         */
        class Window : public core::ecs::Resource {
            friend class WindowProperties;

            public:
            typedef void (*KeyCallback)(core::input::InputManager& manager, const int key, const bool down);
            typedef void (*CursorCallback)(core::input::InputManager& manager, const float xpos, const float ypos);
            typedef void (*MouseButtonCallback)(core::input::InputManager& manager, const int button, const bool down);
            typedef void (*ScrollCallback)(core::input::InputManager& manager, const float xoffset, const float yoffset);
            typedef void (*FramebufferResizeCallback)(gfx::Window& window, const uint width, const uint height);
            typedef void (*ResizeCallback)(gfx::Window& window, const uint width, const uint height);

            /**
             * @brief: Creates a new window.
             * @param properties: The properties of the window.
             * @return: A new window.
             */
            static Window create(const WindowProperties& properties) noexcept;

            /**
             * @brief: Destroys the window.
             */
            ~Window();
            /**
             * @brief: Default move constructor.
             */
            Window(Window&&) noexcept;

            /**
             * @brief: Initializes the window. Called on construction and after changing window hints.
             * @return: void
             */
            void init();
            /**
             * @brief: Swap the front and back buffers of the window.
             * @return: void
             */
            void swapBuffers() const;
            /**
             * @brief: Switches the mode of the window. VAOs and VBOs are not preserved, so make sure to rebuild your scene after switching the mode
             * of the window.
             * @param mode: The new mode of the window.
             * @return: void
             */
            void switchMode(const WindowMode mode);
            /**
             * @brief: Makes the window visible
             * @return: void
             */
            void show() const;
            /**
             * @brief: Hides the window.
             * @return: void
             */
            void hide() const;
            /**
             * @brief: Clears the screen to the default color.
             * @return: void
             */
            void clear();
            /**
             * @brief: Checks if the window should close.
             * @return: Whether or not the window should close.
             */
            bool shouldClose() const;
            /**
             * @brief: Sets the clear color of the window.
             * @param color: The color to clear the screen to.
             * @return: void
             */
            void setClearColor(const Color& color);
            /**
             * @brief: Call to resize the GLFW window to match this window's dimensions.
             * @return: void
             */
            void resize();

            /**
             * @brief: Gets the width of the window.
             * @return: The width of the window.
             */
            const uint getWidth() const;
            /**
             * @brief: Gets the height of the window.
             * @return: The height of the window.
             */
            const uint getHeight() const;
            /**
             * @brief: Gets the default framebuffer object of the window.
             * @return: The default framebuffer object of the window.
             */
            gl::FBO& getDefaultFBO();
            /**
             * @brief: Gets the default framebuffer object of the window.
             * @return: The default framebuffer object of the window.
             */
            const gl::FBO& getDefaultFBO() const;
            /**
             * @brief: Gets whether or not the window is using vsync.
             * @return: Whether or not the window is using vsync.
             */
            const bool isVsync() const;
            /**
             * @brief: Gets the mode of the window.
             * @return: The mode of the window.
             */
            const WindowMode getMode() const;

            /**
             * @brief: Sets the dimensions of the window.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             * @return: void
             */
            void setDimensions(const uint width, const uint height);
            /**
             * @brief: Sets whether or not the window is using vsync.
             * @param vsync: Whether or not the window is using vsync.
             * @return: void
             */
            void setVsync(const bool vsync);
            /**
             * @brief: Sets the mode of the window.
             * @param mode: The new mode of the window.
             * @return: void
             */
            void setMode(const WindowMode mode);
            /**
             * @brief: Sets the title of the window.
             * @param title: The new title of the window.
             * @return: void
             */
            void setTitle(const std::string& title);
            /**
             * @brief: Sets the key callback of the window.
             * @param callback: The new key callback of the window.
             * @return: void
             */
            void setKeyCallback(const KeyCallback callback);
            /**
             * @brief: Sets the cursor callback of the window.
             * @param callback: The new cursor callback of the window.
             * @return: void
             */
            void setCursorCallback(const CursorCallback callback);
            /**
             * @brief: Sets the mouse button callback of the window.
             * @param callback: The new mouse button callback of the window.
             * @return: void
             */
            void setMouseButtonCallback(const MouseButtonCallback callback);
            /**
             * @brief: Sets the scroll callback of the window.
             * @param callback: The new scroll callback of the window.
             * @return: void
             */
            void setScrollCallback(const ScrollCallback callback);
            /**
             * @brief: Sets the framebuffer resize callback of the window.
             * @param callback: The new framebuffer resize callback of the window.
             * @return: void
             */
            void setFramebufferResizeCallback(const FramebufferResizeCallback callback);
            /**
             * @brief: Sets the resize callback of the window.
             * @param callback: The new resize callback of the window.
             * @return: void
             */
            void setResizeCallback(const ResizeCallback callback);

            /**
             * @brief: Callback for when a key is pressed or released.
             * @param manager: The input manager.
             * @param key: The GLFW code for the key that was pressed or released.
             * @param down: Whether or not the key was pressed or released.
             * @return: void
             */
            void onKey(input::InputManager& manager, const int key, const bool down);
            /**
             * @brief: Callback for when the cursor is moved.
             * @param manager: The input manager.
             * @param xpos: The new x position of the cursor.
             * @param ypos: The new y position of the cursor.
             * @return: void
             */
            void onCursor(input::InputManager& manager, const float xpos, const float ypos);
            /**
             * @brief: Callback for when a mouse button is pressed or released.
             * @param manager: The input manager.
             * @param button: The GLFW code for the button that was pressed or released.
             * @param down: Whether or not the button was pressed or released.
             * @return: void
             */
            void onMouseButton(input::InputManager& manager, const int button, const bool down);
            /**
             * @brief: Callback for when the scroll wheel is scrolled.
             * @param manager: The input manager.
             * @param xoffset: The x offset of the scroll wheel.
             * @param yoffset: The y offset of the scroll wheel.
             * @return: void
             */
            void onScroll(input::InputManager& manager, const float xoffset, const float yoffset);
            /**
             * @brief: Callback for when the framebuffer is resized.
             * @param width: The new width of the framebuffer.
             * @param height: The new height of the framebuffer.
             * @return: void
             */
            void onFramebufferResize(const uint width, const uint height);
            /**
             * @brief: Callback for when the window is resized.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             * @return: void
             */
            void onResize(const uint width, const uint height);

            private:
            /**
             * @brief: Creates a new window.
             * @param width: The width of the window.
             * @param height: The height of the window.
             * @param title: The title of the window.
             * @param vsync: Whether or not the window should be using vsync.
             * @param mode: The mode of the window.
             * @param resizable: Whether or not the window should be resizable.
             * @param decorated: Whether or not the window should be decorated.
             * @param lockAspectRatio: Whether or not the aspect ratio of the window should be locked.
             * @param keyCallback: The key callback of the window.
             * @param cursorCallback: The cursor callback of the window.
             * @param mouseButtonCallback: The mouse button callback of the window.
             * @param scrollCallback: The scroll callback of the window.
             * @param framebufferResizeCallback: The framebuffer resize callback of the window.
             * @param resizeCallback: The resize callback of the window.
             * @return: A new window.
             */
            Window(const uint width, const uint height, const std::string& title, const bool vsync, const WindowMode mode, const bool resizable,
                   const bool decorated, const bool lockAspectRatio, const KeyCallback keyCallback, const CursorCallback cursorCallback,
                   const MouseButtonCallback mouseButtonCallback, const ScrollCallback scrollCallback,
                   const FramebufferResizeCallback framebufferResizeCallback, const ResizeCallback resizeCallback);

            uint width, height;       // The width and height of the window.
            gl::FBO defaultFBO;       // The default framebuffer object of the window.
            std::string title;        // The title of the window.
            bool vsync;               // Whether or not the window is using vsync.
            bool resizable;           // Whether or not the window is resizable.
            bool decorated;           // Whether or not the window is decorated.
            bool lockAspectRatio;     // Whether or not the aspect ratio of the window is
                                      // locked.
            const float aspectRatio;  // The aspect ratio of the window.
            WindowMode mode;          // The mode of the window.

            KeyCallback keyCallback;                              // The key callback of the window.
            CursorCallback cursorCallback;                        // The cursor callback of the window.
            MouseButtonCallback mouseButtonCallback;              // The mouse button callback of the window.
            ScrollCallback scrollCallback;                        // The scroll callback of the window.
            FramebufferResizeCallback framebufferResizeCallback;  // The framebuffer resize callback of the window.
            ResizeCallback resizeCallback;                        // The resize callback of the window.
        };

        /**
         * @brief: Properties of a GLFW window.
         */
        class WindowProperties {
            friend class Window;

            public:
            /**
             * @brief: Creates a new window properties with default values.
             * @return: A new window properties.
             */
            WindowProperties();
            /**
             * @brief: Destroys the window properties.
             */
            ~WindowProperties() = default;

            /**
             * @brief: Sets the width of the window.
             * @param width: The width of the window.
             * @return: The window properties.
             */
            WindowProperties& setWidth(const uint width);
            /**
             * @brief: Sets the height of the window.
             * @param height: The height of the window.
             * @return: The window properties.
             */
            WindowProperties& setHeight(const uint height);
            /**
             * @brief: Sets the title of the window.
             * @param title: The title of the window.
             * @return: The window properties.
             */
            WindowProperties& setTitle(const std::string& title);
            /**
             * @brief: Sets whether or not the window is using vsync.
             * @param vsync: Whether or not the window is using vsync.
             * @return: The window properties.
             */
            WindowProperties& setVsync(const bool vsync);
            /**
             * @brief: Sets the mode of the window.
             * @param mode: The mode of the window.
             * @return: The window properties.
             */
            WindowProperties& setMode(const WindowMode mode);
            /**
             * @brief: Sets whether or not the window is resizable.
             * @param resizable: Whether or not the window is resizable.
             * @return: The window properties.
             */
            WindowProperties& setResizable(const bool resizable);
            /**
             * @brief: Sets whether or not the window is decorated.
             * @param decorated: Whether or not the window is decorated.
             * @return: The window properties.
             */
            WindowProperties& setDecorated(const bool decorated);
            /**
             * @brief: Locks the aspect ratio of the window.
             * @param lockAspectRatio: The aspect ratio of the window.
             * @return: The window properties.
             */
            WindowProperties& setLockAspectRatio(const bool lockAspectRatio);
            /**
             * @brief: Sets the key callback of the window.
             * @param callback: The key callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setKeyCallback(const Window::KeyCallback callback);
            /**
             * @brief: Sets the cursor callback of the window.
             * @param callback: The cursor callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setCursorCallback(const Window::CursorCallback callback);
            /**
             * @brief: Sets the mouse button callback of the window.
             * @param callback: The mouse button callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setMouseButtonCallback(const Window::MouseButtonCallback callback);
            /**
             * @brief: Sets the scroll callback of the window.
             * @param callback: The scroll callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setScrollCallback(const Window::ScrollCallback callback);
            /**
             * @brief: Sets the framebuffer resize callback of the window.
             * @param callback: The framebuffer resize callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setFramebufferResizeCallback(const Window::FramebufferResizeCallback callback);
            /**
             * @brief: Sets the resize callback of the window.
             * @param callback: The resize callback of the window.
             * @return: The window properties.
             */
            WindowProperties& setResizeCallback(const Window::ResizeCallback callback);

            private:
            uint width, height;
            std::string title;
            bool vsync;
            WindowMode mode;
            bool resizable;
            bool decorated;
            bool lockAspectRatio;
            Window::KeyCallback keyCallback;
            Window::CursorCallback cursorCallback;
            Window::MouseButtonCallback mouseButtonCallback;
            Window::ScrollCallback scrollCallback;
            Window::FramebufferResizeCallback framebufferResizeCallback;
            Window::ResizeCallback resizeCallback;

            /**
             * @brief: Builds the window.
             * @return: The window.
             */
            Window getWindow() const;
        };
    }  // namespace core::gfx
}  // namespace cobalt