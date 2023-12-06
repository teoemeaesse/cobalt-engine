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

        enum class GLTextureEncoding {
            R8 = GL_R8,                         // Red channel with 8 bits per channel.
            RG8 = GL_RG8,                       // Red and green channels with 8 bits per channel.
            RGB8 = GL_RGB8,                     // Red, green and blue channels with 8 bits per channel.
            RGBA8 = GL_RGBA8,                   // Red, green, blue and alpha channels with 8 bits per channel.
            SRGB8 = GL_SRGB8,                   // Red, green and blue channels with 8 bits per channel.
            SRGBA8 = GL_SRGB8_ALPHA8           // Red, green, blue and alpha channels with 8 bits per channel.
        };
        inline std::string getGLTextureEncodingName(GLTextureEncoding format) {
            switch (format) {
                case GLTextureEncoding::R8:
                    return "R8";
                case GLTextureEncoding::RG8:
                    return "RG8";
                case GLTextureEncoding::RGB8:
                    return "RGB8";
                case GLTextureEncoding::RGBA8:
                    return "RGBA8";
                case GLTextureEncoding::SRGB8:
                    return "SRGB8";
                case GLTextureEncoding::SRGBA8:
                    return "SRGBA8";
                default:
                    throw GLException("Invalid GLTextureEncoding");
            }
        }

        enum class GLTextureFormat {
            RED = GL_RED,                       // Red channel.
            RG = GL_RG,                         // Red and green channels.
            RGB = GL_RGB,                       // Red, green and blue channels.
            RGBA = GL_RGBA,                     // Red, green, blue and alpha channels.
            DEPTH = GL_DEPTH_COMPONENT,         // Depth component.
            DEPTH_STENCIL = GL_DEPTH_STENCIL    // Depth and stencil components.
        };
        inline std::string getGLTextureFormatName(GLTextureFormat format) {
            switch (format) {
                case GLTextureFormat::RED:
                    return "RED";
                case GLTextureFormat::RG:
                    return "RG";
                case GLTextureFormat::RGB:
                    return "RGB";
                case GLTextureFormat::RGBA:
                    return "RGBA";
                case GLTextureFormat::DEPTH:
                    return "DEPTH";
                case GLTextureFormat::DEPTH_STENCIL:
                    return "DEPTH_STENCIL";
                default:
                    throw GLException("Invalid GLTextureFormat");
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
                    throw GLException("Invalid GLTextureWrap");
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
                    throw GLException("Invalid GLTextureFilter");
            }
        }

        enum class GLFramebufferAttachment {
            Color = 1 << 1,                                 // Color attachment.
            Depth = 1 << 2,                                 // Depth attachment.
            Stencil = 1 << 3,                               // Stencil attachment.
            ColorDepth = Color | Depth,                     // Color and depth attachments.
            ColorStencil = Color | Stencil,                 // Color and stencil attachments.
            DepthStencil = Depth | Stencil,                 // Depth and stencil attachments.
            ColorDepthStencil = Color | Depth | Stencil     // Color, depth and stencil attachments.
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
                    throw GLException("Invalid GLType");
            }
        }
    }
}