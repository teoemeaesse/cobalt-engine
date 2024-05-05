/**
 * @file pch.h
 * @brief Precompiled main library interfaces for the Cobalt core, providing various utilities such as STL and OpenGL wrappers.
 * @author Tomás Marques
 * @date 22-12-2023
 */

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

#include "core/io/file.h"
#include "core/io/path.h"
#include "core/memory/arena.h"
#include "core/memory/heap.h"
#include "core/memory/pool.h"
#include "core/utils/color.h"
#include "core/utils/log.h"
#include "core/utils/platform.h"
#include "json/json.hpp"

/**
 * @brief Macro to create a new scoped pointer.
 */
#define CB_CREATE_SCOPE(T, ...) std::unique_ptr<T>(new T(__VA_ARGS__))
/**
 * @brief Macro to create a new shared pointer.
 */
#define CB_CREATE_SHARED(T, ...) std::shared_ptr<T>(new T(__VA_ARGS__))

/**
 * @brief The Cobalt namespace encapsulates all functionality of the Cobalt engine.
 */
namespace cobalt {
    /**
     * @brief Scoped pointer for automatic resource management.
     * @tparam T Type of the object managed by the scope.
     */
    template <typename T>
    using Scope = std::unique_ptr<T>;
    /**
     * @brief Creates a new scoped pointer.
     * @tparam T Type of the object managed by the scope.
     * @tparam Args Types of the arguments to pass to the constructor.
     * @param args Arguments to pass to the constructor.
     * @return The new scoped pointer.
     */
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    /**
     * @brief Shared pointer for shared resource management.
     * @tparam T Type of the object managed by the shared pointer.
     */
    template <typename T>
    using Shared = std::shared_ptr<T>;
    /**
     * @brief Creates a new shared pointer.
     * @tparam T Type of the object managed by the shared pointer.
     * @tparam Args Types of the arguments to pass to the constructor.
     * @param args Arguments to pass to the constructor.
     * @return The new shared pointer.
     */
    template <typename T, typename... Args>
    constexpr Shared<T> CreateShared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    /**
     * @brief Reference wrapper for reference management.
     * @tparam T Type of the object managed by the reference wrapper.
     */
    template <typename T>
    using Wrap = std::reference_wrapper<T>;
    /**
     * @brief Creates a new reference wrapper.
     * @tparam T Type of the object managed by the reference wrapper.
     * @param ref Reference to wrap.
     * @return The new reference wrapper.
     */
    template <typename T>
    constexpr Wrap<T> CreateWrap(T& ref) {
        return std::ref(ref);
    }
    /**
     * @brief Wrapper for std::unordered_map.
     * @tparam T Type of the key.
     * @tparam S Type of the value.
     */
    template <typename T, typename S>
    using UMap = std::unordered_map<T, S>;
    /**
     * @brief Wrapper for std::unordered_set.
     * @tparam T Type of the element.
     * @tparam S Type of the hash function.
     */
    template <typename T, typename S>
    using USet = std::unordered_set<T, S>;
    /**
     * @brief Wrapper for std::optional.
     * @tparam T Type of the object managed by the optional.
     */
    template <typename T>
    using Opt = std::optional<T>;
    /**
     * @brief Wrapper for std::nullopt.
     */
    inline constexpr auto& None = std::nullopt;
    /**
     * @brief Wrapper for std::tuple.
     * @tparam T Types of the elements.
     */
    template <typename... T>
    using Tuple = std::tuple<T...>;
    /**
     * @brief Wrapper for std::vector.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Vec = std::vector<T>;
    /**
     * @brief Wrapper for std::list.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using List = std::list<T>;
    /**
     * @brief Wrapper for std::deque.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Deque = std::deque<T>;
    /**
     * @brief Wrapper for std::stack.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Stack = std::stack<T>;
    /**
     * @brief Wrapper for std::queue.
     * @tparam T Type of the elements.
     */
    template <typename T>
    using Queue = std::queue<T>;
    /**
     * @brief Wrapper for std::bitset.
     * @tparam N Number of bits.
     */
    template <unsigned int N>
    using Mask = std::bitset<N>;
    /**
     * @brief Alias for an unsigned char.
     */
    using uchar = unsigned char;
    /**
     * @brief Alias for a signed 64-bit integer.
     */
    using int64 = int64_t;
    /**
     * @brief Alias for an unsigned 64-bit integer.
     */
    using uint64 = uint64_t;
    /**
     * @brief Alias for an unsigned 32-bit integer.
     */
    using uint = uint32_t;

    /**
     * @brief Removes the const and reference qualifiers from a type.
     * @tparam T Type to remove the qualifiers from.
     */
    template <typename T>
    using RemoveConstRef = std::remove_const_t<std::remove_reference_t<T>>;
    // /**
    //  * @brief Checks if a type is const qualified.
    //  * @tparam T Type to check.
    //  */
    // template <typename T>
    // struct IsConst : std::integral_constant<bool, std::is_const<T>::value || std::is_const<typename std::remove_reference<T>::type>::value> {};
    /**
     * @brief Const reference type wrapper.
     * @tparam T Type of the object.
     */
    template <typename T>
    using Ref = const T&;
    /**
     * @brief Mutable reference type wrapper.
     * @tparam T Type of the object.
     */
    template <typename T>
    using RefMut = T&;
    /**
     * @brief Wrapper for std::move.
     * @tparam T Type of the object.
     * @param arg Object to move.
     * @return The moved object.
     */
    template <typename T>
    constexpr typename std::remove_reference<T>::type&& Move(T&& arg) noexcept {
        return std::move(arg);
    }
    /**
     * @brief Demangles the type name string (from typeid(T).name()).
     * @param name The mangled name to demangle.
     * @return A string containing the demangled name.
     */
    static inline const std::string demangle(const char* name) noexcept {
        int status = 42;
        std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
        return (status == 0) ? res.get() : name;
    }

    /**
     * @brief Namespace for numerical constants.
     *
     * This namespace includes a series of numeric limits for different data types,
     * as well as some mathematical constants.
     */
    namespace num {
        static inline constexpr uint64_t MAX_UINT64 = std::numeric_limits<uint64_t>::max();  ///< Maximum possible value for uint64_t.
        static inline constexpr int64_t MAX_INT64 = std::numeric_limits<int64_t>::max();     ///< Maximum possible value for int64_t.
        static inline constexpr uint64_t MIN_UINT64 = std::numeric_limits<uint64_t>::min();  ///< Minimum possible value for uint64_t.
        static inline constexpr int64_t MIN_INT64 = std::numeric_limits<int64_t>::min();     ///< Minimum possible value for int64_t.
        static inline constexpr uint32_t MAX_UINT32 = std::numeric_limits<uint32_t>::max();  ///< Maximum possible value for uint32_t.
        static inline constexpr int32_t MAX_INT32 = std::numeric_limits<int32_t>::max();     ///< Maximum possible value for int32_t.
        static inline constexpr uint32_t MIN_UINT32 = std::numeric_limits<uint32_t>::min();  ///< Minimum possible value for uint32_t.
        static inline constexpr int32_t MIN_INT32 = std::numeric_limits<int32_t>::min();     ///< Minimum possible value for int32_t.
        static inline constexpr float MAX_FLOAT = std::numeric_limits<float>::max();         ///< Maximum possible value for float.
        static inline constexpr float MIN_FLOAT = std::numeric_limits<float>::min();         ///< Minimum possible value for float.
        static inline constexpr double MAX_DOUBLE = std::numeric_limits<double>::max();      ///< Maximum possible value for double.
        static inline constexpr double MIN_DOUBLE = std::numeric_limits<double>::min();      ///< Minimum possible value for double.
        static inline constexpr float PI = 3.14159265358979323846f;                          ///< Value of Pi.
        static inline constexpr float TWO_PI = 6.28318530717958647692f;                      ///< Value of two times Pi.
        static inline constexpr float HALF_PI = 1.57079632679489661923f;                     ///< Value of half Pi.
        static inline constexpr float QUARTER_PI = 0.78539816339744830961f;                  ///< Value of a quarter Pi.
        static inline constexpr float E = 2.71828182845904523536f;                           ///< Euler's number.
        static inline constexpr float SQRT_2 = 1.41421356237309504880f;                      ///< Square root of 2.
        static inline constexpr float SQRT_3 = 1.73205080756887729352f;
    }  // namespace num

    namespace core {
        namespace gl {
            /**
             * @brief 32-bit integer type for OpenGL.
             * Uses GLint which is commonly a 32-bit signed integer.
             */
            using Int = GLint;
            /**
             * @brief 32-bit unsigned integer type for OpenGL.
             * Uses GLuint which is commonly a 32-bit unsigned integer.
             */
            using UInt = GLuint;
            /**
             * @brief 32-bit floating point type for OpenGL.
             * Uses GLfloat which is commonly a 32-bit floating point number.
             */
            using Float = GLfloat;
            /**
             * @brief Represents an OpenGL handle type, defined as a 32-bit unsigned integer.
             */
            using Handle = UInt;

            /**
             * @enum Usage
             * @brief Enum class for buffer data usage hints in OpenGL.
             */
            enum class Usage {
                StaticDraw = GL_STATIC_DRAW,    ///< Buffer data will be modified once and used many times.
                DynamicDraw = GL_DYNAMIC_DRAW,  ///< Buffer data will be modified repeatedly and used many times.
                StreamDraw = GL_STREAM_DRAW     ///< Buffer data will be modified once and used a few times.
            };

            /**
             * @enum Type
             * @brief Enum class for specifying the data types in OpenGL operations.
             */
            enum class Type {
                Float = GL_FLOAT,                 ///< 32-bit floating point.
                Int = GL_INT,                     ///< 32-bit integer.
                UnsignedByte = GL_UNSIGNED_BYTE,  ///< Unsigned 8-bit integer.
                UnsignedInt = GL_UNSIGNED_INT     ///< Unsigned 32-bit integer.
            };

            /**
             * @brief Represents an OpenGL texture encoding type as an integer.
             */
            using TextureEncoding = Int;

            /**
             * @brief Contains constants for texture encodings in OpenGL.
             */
            namespace TextureEncodings {
                constexpr TextureEncoding Unknown = 0;  ///< Represents an unknown texture encoding.

                /**
                 * @brief Texture encodings for one-component (red) OpenGL textures.
                 *
                 * It defines standard, unsigned integer, signed integer, floating-point, and normalized versions for 8, 16, and 32 bits per component
                 * where applicable.
                 */
                namespace R {
                    constexpr TextureEncoding Bits8 = GL_R8;    ///< 8-bit red component.
                    constexpr TextureEncoding Bits16 = GL_R16;  ///< 16-bit red component.

                    /**
                     * @brief Unsigned integer texture encodings for one-component textures.
                     */
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_R8UI;    ///< 8-bit unsigned integer.
                        constexpr TextureEncoding Bits16 = GL_R16UI;  ///< 16-bit unsigned integer.
                        constexpr TextureEncoding Bits32 = GL_R32UI;  ///< 32-bit unsigned integer.
                    }  // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for one-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_R8I;    ///< 8-bit signed integer.
                        constexpr TextureEncoding Bits16 = GL_R16I;  ///< 16-bit signed integer.
                        constexpr TextureEncoding Bits32 = GL_R32I;  ///< 32-bit signed integer.
                    }  // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for one-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_R16F;  ///< 16-bit floating point.
                        constexpr TextureEncoding Bits32 = GL_R32F;  ///< 32-bit floating point.
                    }  // namespace Float
                    /**
                     * @brief Normalized texture encodings for one-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_R8_SNORM;    ///< 8-bit normalized signed integer.
                        constexpr TextureEncoding Bits16 = GL_R16_SNORM;  ///< 16-bit normalized signed integer.
                    }  // namespace Normalized
                }  // namespace R
                /**
                 * @brief Namespace RG contains texture encodings for two-component (red-green) OpenGL textures.
                 *
                 * It defines standard, unsigned integer, signed integer, floating-point, and normalized versions
                 * for 8, 16, and 32 bits per component where applicable.
                 */
                namespace RG {
                    constexpr TextureEncoding Bits8 = GL_RG8;    ///< 8-bit red-green components.
                    constexpr TextureEncoding Bits16 = GL_RG16;  ///< 16-bit red-green components.

                    /**
                     * @brief Unsigned integer texture encodings for two-component textures.
                     */
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RG8UI;    ///< 8-bit unsigned integer red-green components.
                        constexpr TextureEncoding Bits16 = GL_RG16UI;  ///< 16-bit unsigned integer red-green components.
                        constexpr TextureEncoding Bits32 = GL_RG32UI;  ///< 32-bit unsigned integer red-green components.
                    }  // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for two-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RG8I;    ///< 8-bit signed integer red-green components.
                        constexpr TextureEncoding Bits16 = GL_RG16I;  ///< 16-bit signed integer red-green components.
                        constexpr TextureEncoding Bits32 = GL_RG32I;  ///< 32-bit signed integer red-green components.
                    }  // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for two-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RG16F;  ///< 16-bit floating point red-green components.
                        constexpr TextureEncoding Bits32 = GL_RG32F;  ///< 32-bit floating point red-green components.
                    }  // namespace Float
                    /**
                     * @brief Normalized texture encodings for two-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RG8_SNORM;    ///< 8-bit normalized signed integer red-green components.
                        constexpr TextureEncoding Bits16 = GL_RG16_SNORM;  ///< 16-bit normalized signed integer red-green components.
                    }  // namespace Normalized
                }  // namespace RG
                /**
                 * @brief Namespace RGB contains texture encodings for three-component (red-green-blue) OpenGL textures.
                 *
                 * It defines standard, unsigned integer, signed integer, floating-point, and normalized versions
                 * for 4, 8, 16, and 32 bits per component where applicable.
                 */
                namespace RGB {
                    constexpr TextureEncoding Bits4 = GL_RGB4;    ///< 4-bit red-green-blue components.
                    constexpr TextureEncoding Bits8 = GL_RGB8;    ///< 8-bit red-green-blue components.
                    constexpr TextureEncoding Bits16 = GL_RGB16;  ///< 16-bit red-green-blue components.

                    /**
                     * @brief Unsigned integer texture encodings for three-component textures.
                     */
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RGB8UI;    ///< 8-bit unsigned integer red-green-blue components.
                        constexpr TextureEncoding Bits16 = GL_RGB16UI;  ///< 16-bit unsigned integer red-green-blue components.
                        constexpr TextureEncoding Bits32 = GL_RGB32UI;  ///< 32-bit unsigned integer red-green-blue components.
                    }  // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for three-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGB8I;    ///< 8-bit signed integer red-green-blue components.
                        constexpr TextureEncoding Bits16 = GL_RGB16I;  ///< 16-bit signed integer red-green-blue components.
                        constexpr TextureEncoding Bits32 = GL_RGB32I;  ///< 32-bit signed integer red-green-blue components.
                    }  // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for three-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGB16F;  ///< 16-bit floating point red-green-blue components.
                        constexpr TextureEncoding Bits32 = GL_RGB32F;  ///< 32-bit floating point red-green-blue components.
                    }  // namespace Float
                    /**
                     * @brief Normalized texture encodings for three-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGB8_SNORM;    ///< 8-bit normalized signed integer red-green-blue components.
                        constexpr TextureEncoding Bits16 = GL_RGB16_SNORM;  ///< 16-bit normalized signed integer red-green-blue components.
                    }  // namespace Normalized
                }  // namespace RGB

                /**
                 * @brief Namespace RGBA contains texture encodings for four-component (red-green-blue-alpha) OpenGL textures.
                 *
                 * It defines standard, unsigned integer, signed integer, floating-point, and normalized versions
                 * for 4, 8, 16, and 32 bits per component where applicable.
                 */
                namespace RGBA {
                    constexpr TextureEncoding Bits4 = GL_RGBA4;    ///< 4-bit red-green-blue-alpha components.
                    constexpr TextureEncoding Bits8 = GL_RGBA8;    ///< 8-bit red-green-blue-alpha components.
                    constexpr TextureEncoding Bits16 = GL_RGBA16;  ///< 16-bit red-green-blue-alpha components.

                    /**
                     * @brief Unsigned integer texture encodings for four-component textures.
                     */
                    namespace Unsigned {
                        constexpr TextureEncoding Bits8 = GL_RGBA8UI;    ///< 8-bit unsigned integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits16 = GL_RGBA16UI;  ///< 16-bit unsigned integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits32 = GL_RGBA32UI;  ///< 32-bit unsigned integer red-green-blue-alpha components.
                    }  // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for four-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGBA8I;    ///< 8-bit signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits16 = GL_RGBA16I;  ///< 16-bit signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits32 = GL_RGBA32I;  ///< 32-bit signed integer red-green-blue-alpha components.
                    }  // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for four-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGBA16F;  ///< 16-bit floating point red-green-blue-alpha components.
                        constexpr TextureEncoding Bits32 = GL_RGBA32F;  ///< 32-bit floating point red-green-blue-alpha components.
                    }  // namespace Float
                    /**
                     * @brief Normalized texture encodings for four-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGBA8_SNORM;    ///< 8-bit normalized signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits16 = GL_RGBA16_SNORM;  ///< 16-bit normalized signed integer red-green-blue-alpha components.
                    }  // namespace Normalized
                }  // namespace RGBA

                /**
                 * @brief Namespace SRGB contains texture encodings for standard RGB color space OpenGL textures.
                 */
                namespace SRGB {
                    constexpr TextureEncoding Bits8 = GL_SRGB8;  ///< 8-bit standard RGB color space.
                }

                /**
                 * @brief Namespace SRGBA contains texture encodings for standard RGB color space with alpha component OpenGL textures.
                 */
                namespace SRGBA {
                    constexpr TextureEncoding Bits8 = GL_SRGB8_ALPHA8;  ///< 8-bit standard RGB color space with alpha.
                }

                /**
                 * @brief Namespace Depth contains texture encodings for depth component OpenGL textures.
                 */
                namespace Depth {
                    constexpr TextureEncoding Bits16 = GL_DEPTH_COMPONENT16;  ///< 16-bit depth component.
                    constexpr TextureEncoding Bits24 = GL_DEPTH_COMPONENT24;  ///< 24-bit depth component.

                    /**
                     * @brief Floating-point texture encodings for depth component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits32 = GL_DEPTH_COMPONENT32F;  ///< 32-bit floating point depth component.
                    }  // namespace Float
                }  // namespace Depth

                /**
                 * @brief Namespace Stencil contains texture encodings for stencil component OpenGL textures, requiring OpenGL 4.4 or higher.
                 */
                namespace Stencil {
                    constexpr TextureEncoding Bits8 = GL_STENCIL_INDEX8;    ///< 8-bit stencil component.
                    constexpr TextureEncoding Bits16 = GL_STENCIL_INDEX16;  ///< 16-bit stencil component.
                }  // namespace Stencil

                /**
                 * @brief Namespace DepthStencil contains texture encodings for combined depth and stencil components OpenGL textures, requiring
                 * OpenGL 4.3 or higher.
                 */
                namespace DepthStencil {
                    constexpr TextureEncoding Bits24_8 = GL_DEPTH24_STENCIL8;  ///< 24-bit depth and 8-bit stencil components combined.

                    /**
                     * @brief Floating-point texture encodings for combined depth and stencil components.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits32_8 =
                            GL_DEPTH32F_STENCIL8;  ///< 32-bit floating point depth and 8-bit stencil components combined.
                    }  // namespace Float
                }  // namespace DepthStencil

            }  // namespace TextureEncodings

            /**
             * @brief Gets the name of a texture encoding.
             * @param encoding The texture encoding.
             * @return The name of the encoding.
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
             * @brief Gets the name of a pixel type.
             * @param type The pixel type.
             * @return The name of the type.
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
             * @brief Gets the pixel type for a texture encoding.
             * @param encoding The texture encoding.
             * @return The pixel type.
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
             * @brief Gets the name of a texture format.
             * @param format The texture format.
             * @return The name of the format.
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
             * @brief Gets the texture format for a texture encoding.
             * @param encoding The texture encoding.
             * @return The texture format.
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
             * @brief Gets the name of a texture wrap.
             * @param wrap The wrap.
             * @return The name of the wrap.
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
             * @brief Gets the name of a texture filter.
             * @param filter The filter.
             * @return The name of the filter.
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
             * @brief Gets the size of a GL Type.
             * @param type The GL Type.
             * @return The size in bytes of the GL Type.
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