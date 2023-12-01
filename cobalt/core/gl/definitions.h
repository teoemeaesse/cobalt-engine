//
// Created by tomas on 30-11-2023.
//

#pragma once

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#include <GLFW/glfw3.h>

#include "core/exceptions/gl_exception.h"


namespace cobalt {
    namespace core {
        /* Usage mode of a buffer object.
        */
        enum class GLUsage {
            StaticDraw = GL_STATIC_DRAW,        // Buffer data will be modified once and used many times.
            DynamicDraw = GL_DYNAMIC_DRAW,      // Buffer data will be modified repeatedly and used many times.
            StreamDraw = GL_STREAM_DRAW         // Buffer data will be modified once and used a few times.
        };

        enum class GLType {
            Float = GL_FLOAT,                   // 32-bit floating point.
            Int = GL_INT,                       // 32-bit integer.
            UnsignedByte = GL_UNSIGNED_BYTE,    // Unsigned 8-bit integer.
            UnsignedInt = GL_UNSIGNED_INT       // Unsigned 32-bit integer.
        };

        enum class GLTextureFormat {
            RGB = GL_RGB,                       // RGB format.
            RGBA = GL_RGBA                      // RGBA format.
        };

        /* Gets the size of a GLType.
         * @param type: The GLType.
         * @return: The size in bytes of the GLType.
         */
        inline size_t getGLTypeSize(GLType type) {
            switch (type) {
                case GLType::Float:
                    return sizeof(GLfloat);
                case GLType::Int:
                    return sizeof(GLint);
                case GLType::UnsignedByte:
                    return sizeof(GLubyte);
                case GLType::UnsignedInt:
                    return sizeof(GLuint);
                default:
                    throw GLException("Invalid GLType.");
            }
        }

        typedef GLuint GLHandle;          // OpenGL object handle.
    }
}