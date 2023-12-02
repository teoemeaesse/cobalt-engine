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
            RGBA = GL_RGBA,                     // RGBA format.
            RGBA8 = GL_RGBA8                    // RGBA format with 8 bits per channel.
        };
        inline std::string getGLTextureFormatName(GLTextureFormat format) {
            switch (format) {
                case GLTextureFormat::RGB:
                    return "RGB";
                case GLTextureFormat::RGBA:
                    return "RGBA";
                case GLTextureFormat::RGBA8:
                    return "RGBA8";
                default:
                    throw GLException("Invalid GLTextureFormat.");
            }
        }

        enum class GLTextureWrap {
            Repeat = GL_REPEAT,                 // Repeats the texture.
            MirroredRepeat = GL_MIRRORED_REPEAT,// Repeats the texture mirrored.
            ClampToEdge = GL_CLAMP_TO_EDGE,     // Clamps the texture to the edge.
            ClampToBorder = GL_CLAMP_TO_BORDER  // Clamps the texture to the border.
        };
        inline std::string getGLTextureWrapName(GLTextureWrap wrap) {
            switch (wrap) {
                case GLTextureWrap::Repeat:
                    return "Repeat";
                case GLTextureWrap::MirroredRepeat:
                    return "MirroredRepeat";
                case GLTextureWrap::ClampToEdge:
                    return "ClampToEdge";
                case GLTextureWrap::ClampToBorder:
                    return "ClampToBorder";
                default:
                    throw GLException("Invalid GLTextureWrap.");
            }
        }

        enum class GLTextureFilter {
            Nearest = GL_NEAREST,               // Nearest neighbor filtering.
            Linear = GL_LINEAR                  // Linear filtering.
        }; // TODO: mipmap filtering support.
        inline std::string getGLTextureFilterName(GLTextureFilter filter) {
            switch (filter) {
                case GLTextureFilter::Nearest:
                    return "Nearest";
                case GLTextureFilter::Linear:
                    return "Linear";
                default:
                    throw GLException("Invalid GLTextureFilter.");
            }
        }

        enum class GLFramebufferAttachment {
            Color = GL_COLOR_ATTACHMENT0,       // Color attachment.
            Depth = GL_DEPTH_ATTACHMENT,        // Depth attachment.
            Stencil = GL_STENCIL_ATTACHMENT     // Stencil attachment.
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