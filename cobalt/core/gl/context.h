// Created by tomas on
// 02-12-2023

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        using GLFWContext = GLFWwindow*;

        /**
         * @brief Singleton class for a GL render context.
         * The render context is the context that is used for rendering.
         * It is shared between all windows and thread-local.
         * Don't attempt to call GLFW functions or OpenGL functions before initializing
         * the render context with init() or alternatively init(GLFWContext), in
         * multithreaded applications.
         */
        class Context {
            public:
            /**
             * @brief Initializes the render context.
             */
            static void init();
            /**
             * @brief Initializes the render context, given a GLFW context.
             * Use when sharing resources between threads.
             * @param window The GLFW context.
             */
            static void init(GLFWContext context);
            /**
             * @brief Destroys the render context.
             */
            static void destroy();
            /**
             * @brief Recreates the render context. Call this to apply changes to window hints.
             * This has the side effect of resetting any windows' dimensions to 1x1 and
             * title to an empty string. Make sure to set these again after calling this.
             */
            static void recreate();
            /**
             * @brief Recreates the render context, given a GLFW context.
             * Use when sharing resources between threads, or when the underlying OpenGL
             * context is still valid.
             * @param oldContext The old GLFW context.
             */
            static void recreateFromContext(GLFWContext oldContext);

            /**
             * @brief Sets the key callback.
             * @param callback The key callback.
             */
            static void setKeyCallback(GLFWkeyfun callback);
            /**
             * @brief Sets the mouse scroll callback.
             * @param callback The mouse scroll callback.
             */
            static void setScrollCallback(GLFWscrollfun callback);
            /**
             * @brief Sets the cursor position callback.
             * @param callback The cursor position callback.
             */
            static void setCursorPosCallback(GLFWcursorposfun callback);
            /**
             * @brief Sets the mouse button callback.
             * @param callback The mouse button callback.
             */
            static void setMouseButtonCallback(GLFWmousebuttonfun callback);
            /**
             * @brief Sets the window resize callback.
             * @param callback The window resize callback.
             */
            static void setResizeCallback(GLFWwindowsizefun callback);
            /**
             * @brief Sets the framebuffer resize callback.
             * @param callback The framebuffer resize callback.
             */
            static void setFramebufferResizeCallback(GLFWframebuffersizefun callback);
            /**
             * @brief Sets the OpenGL debug callback.
             * @param callback The OpenGL debug callback.
             */
            static void setDebugCallback(GLDEBUGPROC callback);
            /**
             * @brief Sets the GLFW error callback.
             * @param callback The error callback.
             */
            static void setErrorCallback(GLFWerrorfun callback);
            /**
             * @brief Enables blending.
             */
            static void enableBlending();
            /**
             * @brief Disables blending.
             */
            static void disableBlending();
            /**
             * @brief Enables depth testing.
             */
            static void enableDepthTest();
            /**
             * @brief Disables depth testing.
             */
            static void disableDepthTest();
            /**
             * @brief Enables writing to the depth buffer.
             */
            static void enableDepthWriting();
            /**
             * @brief Disables writing to the depth buffer.
             */
            static void disableDepthWriting();
            /**
             * @brief Sets the user pointer. This is any pointer that
             * can be used by anyone with the GL render context.
             * @param pointer The user pointer.
             */
            static void setUserPointer(void* pointer);
            /**
             * @brief Retrieves the user pointer.
             * @return The user pointer.
             */
            static void* getUserPointer();

            /**
             * @brief Gets the current GL render context.
             * @return The current GL render context.
             */
            static Shared<Context>& getInstance();

            /**
             * @brief Gets the GLFW context.
             * @return The GLFW context.
             */
            static GLFWContext getGLFWContext();

            // -- OpenGL queries --

            /**
             * @brief Query the OpenGL version.
             * @return The OpenGL version.
             */
            static const char* queryGLVersion();
            /**
             * @brief Query the OpenGL major version.
             * @return The OpenGL major version.
             */
            static const int queryGLMajorVersion();
            /**
             * @brief Query the OpenGL minor version.
             * @return The OpenGL minor version.
             */
            static const int queryGLMinorVersion();
            /**
             * @brief Query the GLSL version.
             * @return The GLSL version.
             */
            static const char* queryGLSLVersion();

            /**
             * @brief Query the maximum number of color attachments for a framebuffer.
             * @return The maximum number of color attachments.
             */
            static const uint queryMaxColorAttachments();
            /**
             * @brief Query the maximum number of textures that can be accessed.
             * by the fragment shader.
             * @return The maximum number of bound textures.
             */
            static const uint queryMaxFragTextureUnits();
            /**
             * @brief Query the maximum number of total bound textures.
             * @return The maximum number of bound textures.
             */
            static const uint queryMaxTotalTextureUnits();

            /**
             * @brief Log all OpenGL queries.
             */
            static void logQueries();

            /**
             * @brief Clear all OpenGL errors.
             */
            static void clearGLErrors();
            /**
             * @brief Check for OpenGL errors.
             */
            static void checkGLErrors();

            /**
             * @brief Creates a new GL render context.
             * @param context The GLFW context.
             * @return A new GL render context.
             */
            Context();
            /**
             * @brief Creates a new GL render context, given a GLFW context.
             * @param context The GLFW context.
             * @return A new GL render context.
             */
            explicit Context(GLFWContext context);
            /**
             * @brief Destroys the GL render context.
             */
            ~Context();

            private:
            GLFWContext context;  // The GLFW context.

            static Shared<Context> instance;  // The current GL render context.
        };
    }  // namespace core::gl
}  // namespace cobalt