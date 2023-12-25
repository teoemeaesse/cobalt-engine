//
// Created by tomas on 22-12-2023.
//

#pragma once

#include <time.h>
#include <memory>
#include <string>
#include <cstring>
#include <cstddef>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <any>
#include <list>
#include <deque>
#include <vector>
#include <stack>
#include <queue>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-volatile"
#include <glm/glm.hpp>
#pragma GCC diagnostic pop
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES
#endif
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "json/json.hpp"

// Exceptions.
#include "core/exceptions/gfx_exception.h"
#include "core/exceptions/gl_exception.h"
#include "core/exceptions/input_exception.h"

// Logging.
#include "core/utils/log.h"

// Graphics.
#include "core/gfx/color.h"

// IO.
#include "core/io/path.h"
#include "core/io/file.h"

// Memory.
#include "core/memory/pool.h"
#include "core/memory/arena.h"
#include "core/memory/heap.h"


namespace cobalt {
    namespace core {
        template<typename T>
        using Scope = std::unique_ptr<T>;
        template<typename T>
        using Ref = std::shared_ptr<T>;
        using uchar = unsigned char;
        using int64 = int64_t;
        using uint64 = uint64_t;
        using uint = unsigned int;
        using GLHandle = GLuint;    // OpenGL handle type.

        template<typename T, typename S>
        using UMap = std::unordered_map<T, S>;
        template<typename T, typename S>
        using USet = std::unordered_set<T, S>;
        template<typename T>
        using Opt = std::optional<T>;
        template<typename T>
        using Vec = std::vector<T>;
        template<typename T>
        using List = std::list<T>;
        template<typename T>
        using Deque = std::deque<T>;
        template<typename T>
        using Stack = std::stack<T>;
        template<typename T>
        using Queue = std::queue<T>;


        /** Usage mode of a buffer object.
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
            RED = GL_RED,                       // Red channel.
            RG = GL_RG,                         // Red and green channels.
            RGB = GL_RGB,                       // Red, green and blue channels.
            RGBA = GL_RGBA,                     // Red, green, blue and alpha channels.
            DEPTH = GL_DEPTH_COMPONENT,         // Depth component.
            DEPTH_STENCIL = GL_DEPTH_STENCIL,   // Depth and stencil components.
            SRGB = GL_SRGB,                     // sRGB color space.
            SRGBA = GL_SRGB_ALPHA,              // sRGB color space with alpha.
            RED_HDR = GL_R32F,                  // Red channel with 32-bit floating point.
            RG_HDR = GL_RG32F,                  // Red and green channels with 32-bit floating point.
            RGB_HDR = GL_RGB32F,                // Red, green and blue channels with 32-bit floating point.
            RGBA_HDR = GL_RGBA32F               // Red, green, blue and alpha channels with 32-bit floating point.
        };
        inline std::string getGLTextureEncodingName(GLTextureEncoding encoding) {
            switch (encoding) {
                case GLTextureEncoding::RED:
                    return "RED";
                case GLTextureEncoding::RG:
                    return "RG";
                case GLTextureEncoding::RGB:
                    return "RGB";
                case GLTextureEncoding::RGBA:
                    return "RGBA";
                case GLTextureEncoding::DEPTH:
                    return "DEPTH";
                case GLTextureEncoding::DEPTH_STENCIL:
                    return "DEPTH_STENCIL";
                case GLTextureEncoding::SRGB:
                    return "SRGB";
                case GLTextureEncoding::SRGBA:
                    return "SRGBA";
                case GLTextureEncoding::RED_HDR:
                    return "RED_HDR";
                case GLTextureEncoding::RG_HDR:
                    return "RG_HDR";
                case GLTextureEncoding::RGB_HDR:
                    return "RGB_HDR";
                case GLTextureEncoding::RGBA_HDR:
                    return "RGBA_HDR";
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

        enum class GLPrimitive {
            Points = GL_POINTS,                 // Points.
            Lines = GL_LINES,                   // Lines.
            LineLoop = GL_LINE_LOOP,            // Line loop.
            LineStrip = GL_LINE_STRIP,          // Line strip.
            Triangles = GL_TRIANGLES,           // Triangles.
            TriangleStrip = GL_TRIANGLE_STRIP,  // Triangle strip.
            TriangleFan = GL_TRIANGLE_FAN       // Triangle fan.
        };

        /** Gets the size of a GLType.
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