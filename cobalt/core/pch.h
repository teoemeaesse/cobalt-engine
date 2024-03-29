// Created by tomas on
// 22-12-2023

#pragma once

#include <cxxabi.h>
#include <signal.h>
#include <time.h>

#include <algorithm>
#include <any>
#include <bitset>
#include <cstddef>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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
#include "core/gfx/exception.h"
#include "core/gl/exception.h"

// Logging.
#include "core/utils/color.h"
#include "core/utils/log.h"

// IO.
#include "core/io/file.h"
#include "core/io/path.h"

// Memory.
#include "core/memory/arena.h"
#include "core/memory/heap.h"
#include "core/memory/pool.h"

// Platform.
#include "core/utils/platform.h"

namespace cobalt {
    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> createScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template <typename T>
    using Shared = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Shared<T> createShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    template <typename T>
    using Wrap = std::reference_wrapper<T>;
    template <typename T>
    constexpr Wrap<T> createWrap(T& ref) {
        return std::ref(ref);
    }
    template <typename T, typename S>
    using UMap = std::unordered_map<T, S>;
    template <typename T, typename S>
    using USet = std::unordered_set<T, S>;
    template <typename T>
    using Opt = std::optional<T>;
    inline constexpr auto& None = std::nullopt;
    template <typename... T>
    using Tuple = std::tuple<T...>;
    template <typename T>
    using Vec = std::vector<T>;
    template <typename T>
    using List = std::list<T>;
    template <typename T>
    using Deque = std::deque<T>;
    template <typename T>
    using Stack = std::stack<T>;
    template <typename T>
    using Queue = std::queue<T>;
    template <unsigned int N>
    using Mask = std::bitset<N>;
    using uchar = unsigned char;
    using int64 = int64_t;
    using uint64 = uint64_t;
    using uint = unsigned int;

    template <typename T>
    using RemoveConstRef = std::remove_const_t<std::remove_reference_t<T>>;
    template <typename T>
    struct IsConst : std::integral_constant<bool, std::is_const<T>::value || std::is_const<typename std::remove_reference<T>::type>::value> {};
    template <typename T>
    using Ref = const T&;
    template <typename T>
    using RefMut = T&;
    template <typename T>
    constexpr typename std::remove_reference<T>::type&& Move(T&& arg) noexcept {
        return std::move(arg);
    }

    static inline const std::string demangle(const char* name) noexcept {
        int status = 42;
        std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
        return (status == 0) ? res.get() : name;
    }

    namespace num {
        static inline constexpr uint64_t MAX_UINT64 = std::numeric_limits<uint64_t>::max();
        static inline constexpr int64_t MAX_INT64 = std::numeric_limits<int64_t>::max();
        static inline constexpr uint64_t MIN_UINT64 = std::numeric_limits<uint64_t>::min();
        static inline constexpr int64_t MIN_INT64 = std::numeric_limits<int64_t>::min();
        static inline constexpr uint MAX_UINT = std::numeric_limits<uint>::max();
        static inline constexpr int MAX_INT = std::numeric_limits<int>::max();
        static inline constexpr uint MIN_UINT = std::numeric_limits<uint>::min();
        static inline constexpr int MIN_INT = std::numeric_limits<int>::min();
        static inline constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
        static inline constexpr float MIN_FLOAT = std::numeric_limits<float>::min();
        static inline constexpr double MAX_DOUBLE = std::numeric_limits<double>::max();
        static inline constexpr double MIN_DOUBLE = std::numeric_limits<double>::min();
        static inline constexpr float PI = 3.14159265358979323846f;
        static inline constexpr float TWO_PI = 6.28318530717958647692f;
        static inline constexpr float HALF_PI = 1.57079632679489661923f;
        static inline constexpr float QUARTER_PI = 0.78539816339744830961f;
        static inline constexpr float E = 2.71828182845904523536f;
        static inline constexpr float SQRT_2 = 1.41421356237309504880f;
        static inline constexpr float SQRT_3 = 1.73205080756887729352f;
    }  // namespace num
    namespace core {
        namespace gl {
            using Int = GLint;      // 32-bit integer.
            using UInt = GLuint;    // 32-bit unsigned integer.
            using Float = GLfloat;  // 32-bit floating point.
            using Handle = UInt;    // OpenGL handle type.

            enum class Usage {
                StaticDraw = GL_STATIC_DRAW,    // Buffer data will be modified once and used many times.
                DynamicDraw = GL_DYNAMIC_DRAW,  // Buffer data will be modified repeatedly and used many times.
                StreamDraw = GL_STREAM_DRAW     // Buffer data will be modified once and used a few times.
            };

            enum class Type {
                Float = GL_FLOAT,                 // 32-bit floating point.
                Int = GL_INT,                     // 32-bit integer.
                UnsignedByte = GL_UNSIGNED_BYTE,  // Unsigned 8-bit integer.
                UnsignedInt = GL_UNSIGNED_INT     // Unsigned 32-bit integer.
            };

            using TextureEncoding = Int;
            namespace TextureEncodings {
                constexpr TextureEncoding Unknown = 0;
                namespace R {
                    constexpr TextureEncoding Bits8 = GL_R8;
                    constexpr TextureEncoding Bits16 = GL_R16;
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_R8UI;
                        constexpr TextureEncoding Bits16 = GL_R16UI;
                        constexpr TextureEncoding Bits32 = GL_R32UI;
                    }  // namespace Unsigned
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_R8I;
                        constexpr TextureEncoding Bits16 = GL_R16I;
                        constexpr TextureEncoding Bits32 = GL_R32I;
                    }  // namespace Integer
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_R16F;
                        constexpr TextureEncoding Bits32 = GL_R32F;
                    }  // namespace Float
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_R8_SNORM;
                        constexpr TextureEncoding Bits16 = GL_R16_SNORM;
                    }  // namespace Normalized
                }  // namespace R
                namespace RG {
                    constexpr TextureEncoding Bits8 = GL_RG8;
                    constexpr TextureEncoding Bits16 = GL_RG16;
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RG8UI;
                        constexpr TextureEncoding Bits16 = GL_RG16UI;
                        constexpr TextureEncoding Bits32 = GL_RG32UI;
                    }  // namespace Unsigned
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RG8I;
                        constexpr TextureEncoding Bits16 = GL_RG16I;
                        constexpr TextureEncoding Bits32 = GL_RG32I;
                    }  // namespace Integer
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RG16F;
                        constexpr TextureEncoding Bits32 = GL_RG32F;
                    }  // namespace Float
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RG8_SNORM;
                        constexpr TextureEncoding Bits16 = GL_RG16_SNORM;
                    }  // namespace Normalized
                }  // namespace RG
                namespace RGB {
                    constexpr TextureEncoding Bits4 = GL_RGB4;
                    constexpr TextureEncoding Bits8 = GL_RGB8;
                    constexpr TextureEncoding Bits16 = GL_RGB16;
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RGB8UI;
                        constexpr TextureEncoding Bits16 = GL_RGB16UI;
                        constexpr TextureEncoding Bits32 = GL_RGB32UI;
                    }  // namespace Unsigned
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGB8I;
                        constexpr TextureEncoding Bits16 = GL_RGB16I;
                        constexpr TextureEncoding Bits32 = GL_RGB32I;
                    }  // namespace Integer
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGB16F;
                        constexpr TextureEncoding Bits32 = GL_RGB32F;
                    }  // namespace Float
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGB8_SNORM;
                        constexpr TextureEncoding Bits16 = GL_RGB16_SNORM;
                    }  // namespace Normalized
                }  // namespace RGB
                namespace RGBA {
                    constexpr TextureEncoding Bits4 = GL_RGBA4;
                    constexpr TextureEncoding Bits8 = GL_RGBA8;
                    constexpr TextureEncoding Bits16 = GL_RGBA16;
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RGBA8UI;
                        constexpr TextureEncoding Bits16 = GL_RGBA16UI;
                        constexpr TextureEncoding Bits32 = GL_RGBA32UI;
                    }  // namespace Unsigned
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGBA8I;
                        constexpr TextureEncoding Bits16 = GL_RGBA16I;
                        constexpr TextureEncoding Bits32 = GL_RGBA32I;
                    }  // namespace Integer
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGBA16F;
                        constexpr TextureEncoding Bits32 = GL_RGBA32F;
                    }  // namespace Float
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGBA8_SNORM;
                        constexpr TextureEncoding Bits16 = GL_RGBA16_SNORM;
                    }  // namespace Normalized
                }  // namespace RGBA
                namespace SRGB {
                    constexpr TextureEncoding Bits8 = GL_SRGB8;
                }
                namespace SRGBA {
                    constexpr TextureEncoding Bits8 = GL_SRGB8_ALPHA8;
                }
                namespace Depth {
                    constexpr TextureEncoding Bits16 = GL_DEPTH_COMPONENT16;
                    constexpr TextureEncoding Bits24 = GL_DEPTH_COMPONENT24;
                    namespace Float {
                        constexpr TextureEncoding Bits32 = GL_DEPTH_COMPONENT32F;
                    }
                }  // namespace Depth
                namespace Stencil {  // OpenGL 4.4 or higher.
                    constexpr TextureEncoding Bits8 = GL_STENCIL_INDEX8;
                    constexpr TextureEncoding Bits16 = GL_STENCIL_INDEX16;
                }  // namespace Stencil
                namespace DepthStencil {  // Accessing stencil specifically requires OpenGL 4.3
                                          // or higher.
                    constexpr TextureEncoding Bits24_8 = GL_DEPTH24_STENCIL8;
                    namespace Float {
                        constexpr TextureEncoding Bits32_8 = GL_DEPTH32F_STENCIL8;
                    }
                }  // namespace DepthStencil
            }  // namespace TextureEncodings
            /**
             * @brief: Gets the name of a texture encoding.
             * @param encoding: The texture encoding.
             * @return: The name of the encoding.
             */
            inline std::string getTextureEncodingName(const TextureEncoding encoding) noexcept {
                switch (encoding) {
                    case TextureEncodings::R::Bits8:
                        return "8-bit red";
                    case TextureEncodings::R::Bits16:
                        return "16-bit red";
                    case TextureEncodings::R::Unsigned::Bits8:
                        return "8-bit uint red";
                    case TextureEncodings::R::Unsigned::Bits16:
                        return "16-bit uint red";
                    case TextureEncodings::R::Unsigned::Bits32:
                        return "32-bit uint red";
                    case TextureEncodings::R::Integer::Bits8:
                        return "8-bit int red";
                    case TextureEncodings::R::Integer::Bits16:
                        return "16-bit int red";
                    case TextureEncodings::R::Integer::Bits32:
                        return "32-bit int red";
                    case TextureEncodings::R::Float::Bits16:
                        return "16-bit float red";
                    case TextureEncodings::R::Float::Bits32:
                        return "32-bit float red";
                    case TextureEncodings::R::Normalized::Bits8:
                        return "8-bit normalized red";
                    case TextureEncodings::R::Normalized::Bits16:
                        return "16-bit normalized red";
                    case TextureEncodings::RG::Bits8:
                        return "8-bit red-green";
                    case TextureEncodings::RG::Bits16:
                        return "16-bit red-green";
                    case TextureEncodings::RG::Unsigned::Bits8:
                        return "8-bit uint red-green";
                    case TextureEncodings::RG::Unsigned::Bits16:
                        return "16-bit uint red-green";
                    case TextureEncodings::RG::Unsigned::Bits32:
                        return "32-bit uint red-green";
                    case TextureEncodings::RG::Integer::Bits8:
                        return "8-bit int red-green";
                    case TextureEncodings::RG::Integer::Bits16:
                        return "16-bit int red-green";
                    case TextureEncodings::RG::Integer::Bits32:
                        return "32-bit int red-green";
                    case TextureEncodings::RG::Float::Bits16:
                        return "16-bit float red-green";
                    case TextureEncodings::RG::Float::Bits32:
                        return "32-bit float red-green";
                    case TextureEncodings::RG::Normalized::Bits8:
                        return "8-bit normalized red-green";
                    case TextureEncodings::RG::Normalized::Bits16:
                        return "16-bit normalized red-green";
                    case TextureEncodings::RGB::Bits4:
                        return "4-bit RGB";
                    case TextureEncodings::RGB::Bits8:
                        return "8-bit RGB";
                    case TextureEncodings::RGB::Bits16:
                        return "16-bit RGB";
                    case TextureEncodings::RGB::Unsigned::Bits8:
                        return "8-bit uint RGB";
                    case TextureEncodings::RGB::Unsigned::Bits16:
                        return "16-bit uint RGB";
                    case TextureEncodings::RGB::Unsigned::Bits32:
                        return "32-bit uint RGB";
                    case TextureEncodings::RGB::Integer::Bits8:
                        return "8-bit int RGB";
                    case TextureEncodings::RGB::Integer::Bits16:
                        return "16-bit int RGB";
                    case TextureEncodings::RGB::Integer::Bits32:
                        return "32-bit int RGB";
                    case TextureEncodings::RGB::Float::Bits16:
                        return "16-bit float RGB";
                    case TextureEncodings::RGB::Float::Bits32:
                        return "32-bit float RGB";
                    case TextureEncodings::RGB::Normalized::Bits8:
                        return "8-bit normalized RGB";
                    case TextureEncodings::RGB::Normalized::Bits16:
                        return "16-bit normalized RGB";
                    case TextureEncodings::RGBA::Bits4:
                        return "4-bit RGBA";
                    case TextureEncodings::RGBA::Bits8:
                        return "8-bit RGBA";
                    case TextureEncodings::RGBA::Bits16:
                        return "16-bit RGBA";
                    case TextureEncodings::RGBA::Unsigned::Bits8:
                        return "8-bit uint RGBA";
                    case TextureEncodings::RGBA::Unsigned::Bits16:
                        return "16-bit uint RGBA";
                    case TextureEncodings::RGBA::Unsigned::Bits32:
                        return "32-bit uint RGBA";
                    case TextureEncodings::RGBA::Integer::Bits8:
                        return "8-bit int RGBA";
                    case TextureEncodings::RGBA::Integer::Bits16:
                        return "16-bit int RGBA";
                    case TextureEncodings::RGBA::Integer::Bits32:
                        return "32-bit int RGBA";
                    case TextureEncodings::RGBA::Float::Bits16:
                        return "16-bit float RGBA";
                    case TextureEncodings::RGBA::Float::Bits32:
                        return "32-bit float RGBA";
                    case TextureEncodings::RGBA::Normalized::Bits8:
                        return "8-bit normalized RGBA";
                    case TextureEncodings::RGBA::Normalized::Bits16:
                        return "16-bit normalized RGBA";
                    case TextureEncodings::SRGB::Bits8:
                        return "8-bit sRGB";
                    case TextureEncodings::SRGBA::Bits8:
                        return "8-bit sRGBA";
                    case TextureEncodings::Depth::Bits16:
                        return "16-bit depth";
                    case TextureEncodings::Depth::Bits24:
                        return "24-bit depth";
                    case TextureEncodings::Depth::Float::Bits32:
                        return "32-bit float depth";
                    case TextureEncodings::Stencil::Bits8:
                        return "8-bit stencil";
                    case TextureEncodings::Stencil::Bits16:
                        return "16-bit stencil";
                    case TextureEncodings::DepthStencil::Bits24_8:
                        return "24-bit depth + 8-bit stencil";
                    case TextureEncodings::DepthStencil::Float::Bits32_8:
                        return "32-bit float depth + 8-bit stencil";
                    case TextureEncodings::Unknown:
                    default:
                        return "Unknown encoding";
                }
            }

            using PixelType = Int;
            namespace PixelTypes {
                constexpr PixelType Unknown = 0;
                constexpr PixelType UnsignedByte = GL_UNSIGNED_BYTE;
                constexpr PixelType UnsignedShort = GL_UNSIGNED_SHORT;
                constexpr PixelType UnsignedInt = GL_UNSIGNED_INT;
                constexpr PixelType Byte = GL_BYTE;
                constexpr PixelType Short = GL_SHORT;
                constexpr PixelType Int = GL_INT;
                constexpr PixelType HalfFloat = GL_HALF_FLOAT;
                constexpr PixelType Float = GL_FLOAT;
            }  // namespace PixelTypes
            /**
             * @brief: Gets the name of a pixel type.
             * @param type: The pixel type.
             * @return: The name of the type.
             */
            inline std::string getPixelTypeName(const PixelType type) noexcept {
                switch (type) {
                    case PixelTypes::UnsignedByte:
                        return "Unsigned byte";
                    case PixelTypes::UnsignedShort:
                        return "Unsigned short";
                    case PixelTypes::UnsignedInt:
                        return "Unsigned int";
                    case PixelTypes::Byte:
                        return "Byte";
                    case PixelTypes::Short:
                        return "Short";
                    case PixelTypes::Int:
                        return "Int";
                    case PixelTypes::HalfFloat:
                        return "Half float";
                    case PixelTypes::Float:
                        return "Float";
                    case PixelTypes::Unknown:
                    default:
                        return "Unknown type";
                }
            }
            /**
             * @brief: Gets the pixel type for a texture encoding.
             * @param encoding: The texture encoding.
             * @return: The pixel type.
             */
            inline const PixelType getPixelType(const TextureEncoding encoding) noexcept {
                switch (encoding) {
                    case TextureEncodings::R::Unsigned::Bits8:
                    case TextureEncodings::RG::Unsigned::Bits8:
                    case TextureEncodings::RGB::Unsigned::Bits8:
                    case TextureEncodings::RGBA::Unsigned::Bits8:
                        return PixelTypes::UnsignedByte;
                    case TextureEncodings::R::Unsigned::Bits16:
                    case TextureEncodings::RG::Unsigned::Bits16:
                    case TextureEncodings::RGB::Unsigned::Bits16:
                    case TextureEncodings::RGBA::Unsigned::Bits16:
                        return PixelTypes::UnsignedShort;
                    case TextureEncodings::R::Unsigned::Bits32:
                    case TextureEncodings::RG::Unsigned::Bits32:
                    case TextureEncodings::RGB::Unsigned::Bits32:
                    case TextureEncodings::RGBA::Unsigned::Bits32:
                        return PixelTypes::UnsignedInt;
                    case TextureEncodings::R::Integer::Bits8:
                    case TextureEncodings::RG::Integer::Bits8:
                    case TextureEncodings::RGB::Integer::Bits8:
                    case TextureEncodings::RGBA::Integer::Bits8:
                        return PixelTypes::Byte;
                    case TextureEncodings::R::Integer::Bits16:
                    case TextureEncodings::RG::Integer::Bits16:
                    case TextureEncodings::RGB::Integer::Bits16:
                    case TextureEncodings::RGBA::Integer::Bits16:
                        return PixelTypes::Short;
                    case TextureEncodings::R::Integer::Bits32:
                    case TextureEncodings::RG::Integer::Bits32:
                    case TextureEncodings::RGB::Integer::Bits32:
                    case TextureEncodings::RGBA::Integer::Bits32:
                        return PixelTypes::Int;
                    case TextureEncodings::R::Float::Bits16:
                    case TextureEncodings::RG::Float::Bits16:
                    case TextureEncodings::RGB::Float::Bits16:
                    case TextureEncodings::RGBA::Float::Bits16:
                    case TextureEncodings::Depth::Float::Bits32:
                        return PixelTypes::HalfFloat;
                    case TextureEncodings::R::Float::Bits32:
                    case TextureEncodings::RG::Float::Bits32:
                    case TextureEncodings::RGB::Float::Bits32:
                    case TextureEncodings::RGBA::Float::Bits32:
                        return PixelTypes::Float;
                    default:
                        return PixelTypes::UnsignedByte;
                }
            }

            using TextureFormat = Int;
            namespace TextureFormats {
                constexpr TextureFormat Unknown = 0;
                constexpr TextureFormat R = GL_RED;
                constexpr TextureFormat RG = GL_RG;
                constexpr TextureFormat RGB = GL_RGB;
                constexpr TextureFormat RGBA = GL_RGBA;
                constexpr TextureFormat RInt = GL_RED_INTEGER;
                constexpr TextureFormat RGInt = GL_RG_INTEGER;
                constexpr TextureFormat RGBInt = GL_RGB_INTEGER;
                constexpr TextureFormat RGBAInt = GL_RGBA_INTEGER;
                constexpr TextureFormat Depth = GL_DEPTH_COMPONENT;
                constexpr TextureFormat Stencil = GL_STENCIL_INDEX;  // OpenGL 4.4 or higher.
                constexpr TextureFormat DepthStencil = GL_DEPTH_STENCIL;
            }  // namespace TextureFormats
            /**
             * @brief: Gets the name of a texture format.
             * @param format: The texture format.
             * @return: The name of the format.
             */
            inline std::string getTextureFormatName(const TextureFormat format) noexcept {
                switch (format) {
                    case TextureFormats::R:
                        return "Red";
                    case TextureFormats::RInt:
                        return "Red int";
                    case TextureFormats::RG:
                        return "Red + green";
                    case TextureFormats::RGInt:
                        return "Red + green int";
                    case TextureFormats::RGB:
                        return "RGB";
                    case TextureFormats::RGBInt:
                        return "RGB int";
                    case TextureFormats::RGBA:
                        return "RGBA";
                    case TextureFormats::RGBAInt:
                        return "RGBA int";
                    case TextureFormats::Depth:
                        return "Depth";
                    case TextureFormats::Stencil:
                        return "Stencil";
                    case TextureFormats::DepthStencil:
                        return "Depth + stencil";
                    case TextureFormats::Unknown:
                    default:
                        return "Unknown format";
                }
            }
            /**
             * @brief: Gets the texture format for a texture encoding.
             * @param encoding: The texture encoding.
             * @return: The texture format.
             */
            inline const TextureFormat getTextureFormat(const TextureEncoding encoding) noexcept {
                switch (encoding) {
                    case TextureEncodings::Unknown:
                        return TextureFormats::Unknown;
                    case TextureEncodings::R::Bits8:
                    case TextureEncodings::R::Bits16:
                    case TextureEncodings::R::Float::Bits16:
                    case TextureEncodings::R::Float::Bits32:
                    case TextureEncodings::R::Normalized::Bits8:
                    case TextureEncodings::R::Normalized::Bits16:
                        return TextureFormats::R;
                    case TextureEncodings::R::Unsigned::Bits8:
                    case TextureEncodings::R::Unsigned::Bits16:
                    case TextureEncodings::R::Unsigned::Bits32:
                    case TextureEncodings::R::Integer::Bits8:
                    case TextureEncodings::R::Integer::Bits16:
                    case TextureEncodings::R::Integer::Bits32:
                        return TextureFormats::RInt;
                    case TextureEncodings::RG::Bits8:
                    case TextureEncodings::RG::Bits16:
                    case TextureEncodings::RG::Float::Bits16:
                    case TextureEncodings::RG::Float::Bits32:
                    case TextureEncodings::RG::Normalized::Bits8:
                    case TextureEncodings::RG::Normalized::Bits16:
                        return TextureFormats::RG;
                    case TextureEncodings::RG::Unsigned::Bits8:
                    case TextureEncodings::RG::Unsigned::Bits16:
                    case TextureEncodings::RG::Unsigned::Bits32:
                    case TextureEncodings::RG::Integer::Bits8:
                    case TextureEncodings::RG::Integer::Bits16:
                    case TextureEncodings::RG::Integer::Bits32:
                        return TextureFormats::RGInt;
                    case TextureEncodings::RGB::Bits4:
                    case TextureEncodings::RGB::Bits8:
                    case TextureEncodings::RGB::Bits16:
                    case TextureEncodings::RGB::Float::Bits16:
                    case TextureEncodings::RGB::Float::Bits32:
                    case TextureEncodings::RGB::Normalized::Bits8:
                    case TextureEncodings::RGB::Normalized::Bits16:
                        return TextureFormats::RGB;
                    case TextureEncodings::RGB::Unsigned::Bits8:
                    case TextureEncodings::RGB::Unsigned::Bits16:
                    case TextureEncodings::RGB::Unsigned::Bits32:
                    case TextureEncodings::RGB::Integer::Bits8:
                    case TextureEncodings::RGB::Integer::Bits16:
                    case TextureEncodings::RGB::Integer::Bits32:
                        return TextureFormats::RGBInt;
                    case TextureEncodings::RGBA::Bits4:
                    case TextureEncodings::RGBA::Bits8:
                    case TextureEncodings::RGBA::Bits16:
                    case TextureEncodings::RGBA::Float::Bits16:
                    case TextureEncodings::RGBA::Float::Bits32:
                    case TextureEncodings::RGBA::Normalized::Bits8:
                    case TextureEncodings::RGBA::Normalized::Bits16:
                        return TextureFormats::RGBA;
                    case TextureEncodings::RGBA::Unsigned::Bits8:
                    case TextureEncodings::RGBA::Unsigned::Bits16:
                    case TextureEncodings::RGBA::Unsigned::Bits32:
                    case TextureEncodings::RGBA::Integer::Bits8:
                    case TextureEncodings::RGBA::Integer::Bits16:
                    case TextureEncodings::RGBA::Integer::Bits32:
                        return TextureFormats::RGBAInt;
                    case TextureEncodings::SRGB::Bits8:
                        return TextureFormats::RGB;
                    case TextureEncodings::SRGBA::Bits8:
                        return TextureFormats::RGBA;
                    case TextureEncodings::Depth::Bits16:
                    case TextureEncodings::Depth::Bits24:
                    case TextureEncodings::Depth::Float::Bits32:
                        return TextureFormats::Depth;
                    case TextureEncodings::Stencil::Bits8:
                    case TextureEncodings::Stencil::Bits16:
                        return TextureFormats::Stencil;
                    case TextureEncodings::DepthStencil::Bits24_8:
                    case TextureEncodings::DepthStencil::Float::Bits32_8:
                        return TextureFormats::DepthStencil;
                }
            }

            using TextureWrap = Int;
            namespace TextureWraps {
                constexpr TextureWrap Unknown = 0;
                constexpr TextureWrap Repeat = GL_REPEAT;
                constexpr TextureWrap MirroredRepeat = GL_MIRRORED_REPEAT;
                constexpr TextureWrap ClampToEdge = GL_CLAMP_TO_EDGE;
                constexpr TextureWrap ClampToBorder = GL_CLAMP_TO_BORDER;
            }  // namespace TextureWraps
            /**
             * @brief: Gets the name of a texture wrap.
             * @param wrap: The wrap.
             * @return: The name of the wrap.
             */
            inline std::string getTextureWrapName(const TextureWrap wrap) noexcept {
                switch (wrap) {
                    case TextureWraps::Repeat:
                        return "Repeat";
                    case TextureWraps::MirroredRepeat:
                        return "Mirrored repeat";
                    case TextureWraps::ClampToEdge:
                        return "Clamp to edge";
                    case TextureWraps::ClampToBorder:
                        return "Clamp to border";
                    case TextureWraps::Unknown:
                    default:
                        return "Unknown wrap";
                }
            }

            using TextureFilter = Int;
            namespace TextureFilters {
                constexpr TextureFilter Unknown = 0;
                constexpr TextureFilter Nearest = GL_NEAREST;
                constexpr TextureFilter Linear = GL_LINEAR;
            }  // namespace TextureFilters
            /**
             * @brief: Gets the name of a texture filter.
             * @param filter: The filter.
             * @return: The name of the filter.
             */
            inline std::string getTextureFilterName(const TextureFilter filter) noexcept {
                switch (filter) {
                    case TextureFilters::Nearest:
                        return "Nearest";
                    case TextureFilters::Linear:
                        return "Linear";
                    case TextureFilters::Unknown:
                    default:
                        return "Unknown filter";
                }
            }

            enum class Primitive {
                Points = GL_POINTS,                 // Points.
                Lines = GL_LINES,                   // Lines.
                LineLoop = GL_LINE_LOOP,            // Line loop.
                LineStrip = GL_LINE_STRIP,          // Line strip.
                Triangles = GL_TRIANGLES,           // Triangles.
                TriangleStrip = GL_TRIANGLE_STRIP,  // Triangle strip.
                TriangleFan = GL_TRIANGLE_FAN       // Triangle fan.
            };
            /**
             * @brief: Gets the size of a GL Type.
             * @param type: The GL Type.
             * @return: The size in bytes of the GL Type.
             */
            inline const size_t getTypeSize(const Type type) noexcept {
                switch (type) {
                    case Type::Float:
                        return sizeof(GLfloat);
                    case Type::Int:
                        return sizeof(GLint);
                    case Type::UnsignedByte:
                        return sizeof(GLubyte);
                    case Type::UnsignedInt:
                        return sizeof(GLuint);
                    default:
                        return 0;
                }
            }
        }  // namespace gl
    }  // namespace core
}  // namespace cobalt