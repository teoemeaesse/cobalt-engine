//
// Created by tomas on 02-12-2023.
//

#pragma once

#include <memory>

#include "core/gl/definitions.h"


namespace cobalt {
    namespace core {
        typedef GLFWwindow* GLFWContext;

        /* Singleton class for the render context.
         * The render context is the context that is used for rendering.
         * It is shared between all windows and thread-local.
         * Don't attempt to call GLFW functions or OpenGL functions before initializing
         * the render context with init() or alternatively init(GLFWContext), in multithreaded
         * applications.
         */
        class RenderContext {
            public:
            /* Initializes the render context.
             */
            static void init();
            /* Initializes the render context, given a GLFW context.
             * Use when sharing resources between threads.
             * @param window: The GLFW context.
             */
            static void init(GLFWContext context);
            /* Destroys the render context.
             */
            static void destroy();
            /* Recreates the render context. Call this to apply changes to window hints.
             * This has the side effect of resetting any windows' dimensions to 1x1 and 
             * title to an empty string. Make sure to set these again after calling this.
             */
            static void recreate();

            /* Sets the key callback.
             * @param callback: The key callback.
             */
            static void setKeyCallback(GLFWkeyfun callback);
            /* Sets the mouse scroll callback.
             * @param callback: The mouse scroll callback.
             */
            static void setScrollCallback(GLFWscrollfun callback);
            /* Sets the cursor position callback.
             * @param callback: The cursor position callback.
             */
            static void setCursorPosCallback(GLFWcursorposfun callback);
            /* Sets the mouse button callback.
             * @param callback: The mouse button callback.
             */
            static void setMouseButtonCallback(GLFWmousebuttonfun callback);
            /* Sets the window resize callback.
             * @param callback: The window resize callback.
             */
            static void setResizeCallback(GLFWwindowsizefun callback);
            /* Sets the GLFW error callback.
             * @param callback: The error callback.
             */
            static void setErrorCallback(GLFWerrorfun callback);
            /* Enables blending.
             */
            static void enableBlending();
            /* Disables blending.
             */
            static void disableBlending();
            /* Enables depth testing.
             */
            static void enableDepthTest();
            /* Disables depth testing.
             */
            static void disableDepthTest();
            /* Sets the user pointer. This is any pointer that
             * can be used by anyone with the render context.
             * @param pointer: The user pointer.
             */
            static void setUserPointer(void* pointer);
            /* Retrieves the user pointer.
             * @return: The user pointer.
             */
            static void* getUserPointer();

            /* Gets the current render context.
             * @return: The current render context.
             */
            static std::shared_ptr<RenderContext>& getInstance();

            /* Gets the GLFW context.
             * @return: The GLFW context.
             */
            static GLFWContext getGLFWContext();

            /* Creates a new render context.
             * @param context: The GLFW context.
             * @return: A new render context.
             */
            RenderContext();
            /* Creates a new render context, given a GLFW context.
             * @param context: The GLFW context.
             * @return: A new render context.
             */
            RenderContext(GLFWContext context);
            /* Destroys the render context.
             */
            ~RenderContext();

            private:
            GLFWContext context;                                // The GLFW context.

            static std::shared_ptr<RenderContext> instance;     // The current render context.
        };
    }
}