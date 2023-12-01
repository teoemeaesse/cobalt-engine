//
// Created by tomas on 30-11-2023.
//

#pragma once

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#include <GLFW/glfw3.h>


namespace cobalt {
    namespace core {
        /* Usage mode of a buffer object.
        */
        enum class GLUsage {
            StaticDraw = GL_STATIC_DRAW,        // Buffer data will be modified once and used many times.
            DynamicDraw = GL_DYNAMIC_DRAW,      // Buffer data will be modified repeatedly and used many times.
            StreamDraw = GL_STREAM_DRAW         // Buffer data will be modified once and used a few times.
        };

        typedef GLuint GLHandle;          // OpenGL object handle.
    }
}