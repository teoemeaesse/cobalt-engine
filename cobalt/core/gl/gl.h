/**
 * @file gl.h
 * @brief Defines useful constants and function wrappers for OpenGL.
 * @author Tomás Marques
 * @date 06-05-2024
 */

#pragma once

#ifndef COBALT_CORE_GL_H
#define COBALT_CORE_GL_H
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
#endif

namespace cobalt {
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
                    }                                                 // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for one-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_R8I;    ///< 8-bit signed integer.
                        constexpr TextureEncoding Bits16 = GL_R16I;  ///< 16-bit signed integer.
                        constexpr TextureEncoding Bits32 = GL_R32I;  ///< 32-bit signed integer.
                    }                                                // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for one-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_R16F;  ///< 16-bit floating point.
                        constexpr TextureEncoding Bits32 = GL_R32F;  ///< 32-bit floating point.
                    }                                                // namespace Float
                    /**
                     * @brief Normalized texture encodings for one-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_R8_SNORM;    ///< 8-bit normalized signed integer.
                        constexpr TextureEncoding Bits16 = GL_R16_SNORM;  ///< 16-bit normalized signed integer.
                    }                                                     // namespace Normalized
                }                                                         // namespace R
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
                    }                                                  // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for two-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RG8I;    ///< 8-bit signed integer red-green components.
                        constexpr TextureEncoding Bits16 = GL_RG16I;  ///< 16-bit signed integer red-green components.
                        constexpr TextureEncoding Bits32 = GL_RG32I;  ///< 32-bit signed integer red-green components.
                    }                                                 // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for two-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RG16F;  ///< 16-bit floating point red-green components.
                        constexpr TextureEncoding Bits32 = GL_RG32F;  ///< 32-bit floating point red-green components.
                    }                                                 // namespace Float
                    /**
                     * @brief Normalized texture encodings for two-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RG8_SNORM;    ///< 8-bit normalized signed integer red-green components.
                        constexpr TextureEncoding Bits16 = GL_RG16_SNORM;  ///< 16-bit normalized signed integer red-green components.
                    }                                                      // namespace Normalized
                }                                                          // namespace RG
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
                    }                                                   // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for three-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGB8I;    ///< 8-bit signed integer red-green-blue components.
                        constexpr TextureEncoding Bits16 = GL_RGB16I;  ///< 16-bit signed integer red-green-blue components.
                        constexpr TextureEncoding Bits32 = GL_RGB32I;  ///< 32-bit signed integer red-green-blue components.
                    }                                                  // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for three-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGB16F;  ///< 16-bit floating point red-green-blue components.
                        constexpr TextureEncoding Bits32 = GL_RGB32F;  ///< 32-bit floating point red-green-blue components.
                    }                                                  // namespace Float
                    /**
                     * @brief Normalized texture encodings for three-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGB8_SNORM;    ///< 8-bit normalized signed integer red-green-blue components.
                        constexpr TextureEncoding Bits16 = GL_RGB16_SNORM;  ///< 16-bit normalized signed integer red-green-blue components.
                    }                                                       // namespace Normalized
                }                                                           // namespace RGB

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
                    }                                                    // namespace Unsigned
                    /**
                     * @brief Signed integer texture encodings for four-component textures.
                     */
                    namespace Integer {
                        constexpr TextureEncoding Bits8 = GL_RGBA8I;    ///< 8-bit signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits16 = GL_RGBA16I;  ///< 16-bit signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits32 = GL_RGBA32I;  ///< 32-bit signed integer red-green-blue-alpha components.
                    }                                                   // namespace Integer
                    /**
                     * @brief Floating-point texture encodings for four-component textures.
                     */
                    namespace Float {
                        constexpr TextureEncoding Bits16 = GL_RGBA16F;  ///< 16-bit floating point red-green-blue-alpha components.
                        constexpr TextureEncoding Bits32 = GL_RGBA32F;  ///< 32-bit floating point red-green-blue-alpha components.
                    }                                                   // namespace Float
                    /**
                     * @brief Normalized texture encodings for four-component textures.
                     */
                    namespace Normalized {
                        constexpr TextureEncoding Bits8 = GL_RGBA8_SNORM;    ///< 8-bit normalized signed integer red-green-blue-alpha components.
                        constexpr TextureEncoding Bits16 = GL_RGBA16_SNORM;  ///< 16-bit normalized signed integer red-green-blue-alpha components.
                    }                                                        // namespace Normalized
                }                                                            // namespace RGBA

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
                    }                                                              // namespace Float
                }                                                                  // namespace Depth

                /**
                 * @brief Namespace Stencil contains texture encodings for stencil component OpenGL textures, requiring OpenGL 4.4 or higher.
                 */
                namespace Stencil {
                    constexpr TextureEncoding Bits8 = GL_STENCIL_INDEX8;    ///< 8-bit stencil component.
                    constexpr TextureEncoding Bits16 = GL_STENCIL_INDEX16;  ///< 16-bit stencil component.
                }                                                           // namespace Stencil

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
                    }                              // namespace Float
                }                                  // namespace DepthStencil

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

            /**
             * @brief Type alias for integers used to represent different pixel types.
             */
            using PixelType = int;

            /**
             * @brief Namespace containing constants that represent various pixel types.
             */
            namespace PixelTypes {
                constexpr PixelType Unknown = 0;                        ///< Represents an unknown pixel type.
                constexpr PixelType UnsignedByte = GL_UNSIGNED_BYTE;    ///< Represents an unsigned byte pixel type.
                constexpr PixelType UnsignedShort = GL_UNSIGNED_SHORT;  ///< Represents an unsigned short pixel type.
                constexpr PixelType UnsignedInt = GL_UNSIGNED_INT;      ///< Represents an unsigned integer pixel type.
                constexpr PixelType Byte = GL_BYTE;                     ///< Represents a byte pixel type.
                constexpr PixelType Short = GL_SHORT;                   ///< Represents a short pixel type.
                constexpr PixelType Int = GL_INT;                       ///< Represents an integer pixel type.
                constexpr PixelType HalfFloat = GL_HALF_FLOAT;          ///< Represents a half float pixel type.
                constexpr PixelType Float = GL_FLOAT;                   ///< Represents a float pixel type.
            }                                                           // namespace PixelTypes

            /**
             * @brief Gets the name of a pixel type as a string.
             * @param type The pixel type to get the name for.
             * @return The name of the pixel type as a std::string.
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
             * @brief Gets the pixel type corresponding to a texture encoding.
             * @param encoding The texture encoding for which the pixel type is to be determined.
             * @return The corresponding pixel type as a PixelType.
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
                }  // namespace gl
            }      // namespace core

            /**
             * @brief Type alias for integers used to represent different texture formats.
             */
            using TextureFormat = int;

            /**
             * @brief Namespace containing constants that represent various texture formats.
             */
            namespace TextureFormats {
                constexpr TextureFormat Unknown = 0;                      ///< Represents an unknown texture format.
                constexpr TextureFormat R = GL_RED;                       ///< Represents a red channel format.
                constexpr TextureFormat RG = GL_RG;                       ///< Represents a red-green channel format.
                constexpr TextureFormat RGB = GL_RGB;                     ///< Represents a red-green-blue channel format.
                constexpr TextureFormat RGBA = GL_RGBA;                   ///< Represents a red-green-blue-alpha channel format.
                constexpr TextureFormat RInt = GL_RED_INTEGER;            ///< Represents an integer red channel format.
                constexpr TextureFormat RGInt = GL_RG_INTEGER;            ///< Represents an integer red-green channel format.
                constexpr TextureFormat RGBInt = GL_RGB_INTEGER;          ///< Represents an integer red-green-blue channel format.
                constexpr TextureFormat RGBAInt = GL_RGBA_INTEGER;        ///< Represents an integer red-green-blue-alpha channel format.
                constexpr TextureFormat Depth = GL_DEPTH_COMPONENT;       ///< Represents a depth component format.
                constexpr TextureFormat Stencil = GL_STENCIL_INDEX;       ///< Represents a stencil index format (OpenGL 4.4 or higher).
                constexpr TextureFormat DepthStencil = GL_DEPTH_STENCIL;  ///< Represents a combined depth and stencil format.
            }                                                             // namespace TextureFormats

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

            /**
             * @brief Type alias for integers used to represent different texture wrapping modes.
             */
            using TextureWrap = int;

            /**
             * @brief Namespace containing constants that represent various texture wrapping modes.
             */
            namespace TextureWraps {
                constexpr TextureWrap Unknown = 0;         ///< Represents an unknown texture wrapping mode.
                constexpr TextureWrap Repeat = GL_REPEAT;  ///< Texture wraps around if the coordinates exceed the range [0,1].
                constexpr TextureWrap MirroredRepeat =
                    GL_MIRRORED_REPEAT;  ///< Texture mirrors and wraps around if the coordinates exceed the range [0,1].
                constexpr TextureWrap ClampToEdge = GL_CLAMP_TO_EDGE;      ///< Texture coordinates clamped to the range [0,1].
                constexpr TextureWrap ClampToBorder = GL_CLAMP_TO_BORDER;  ///< Texture coordinates clamped to the border when exceeding the range.
            }                                                              // namespace TextureWraps

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

            /**
             * @typedef TextureFilter
             * @brief Type alias for integers used to represent different texture filtering modes.
             */
            using TextureFilter = int;

            /**
             * @brief Namespace containing constants that represent various texture filtering modes.
             */
            namespace TextureFilters {
                constexpr TextureFilter Unknown = 0;           ///< Represents an unknown texture filtering mode.
                constexpr TextureFilter Nearest = GL_NEAREST;  ///< Uses the nearest texel to the texture coordinate as the filtered value.
                constexpr TextureFilter Linear = GL_LINEAR;    ///< Uses a weighted average of the four nearest texels to the texture coordinate.
            }                                                  // namespace TextureFilters

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

            /**
             * @brief Enum class representing different types of graphical primitives.
             */
            enum class Primitive {
                Points = GL_POINTS,                 ///< Represents points.
                Lines = GL_LINES,                   ///< Represents lines.
                LineLoop = GL_LINE_LOOP,            ///< Represents a continuous loop of lines, where each line starts where the last one ended.
                LineStrip = GL_LINE_STRIP,          ///< Represents a series of connected lines.
                Triangles = GL_TRIANGLES,           ///< Represents triangles.
                TriangleStrip = GL_TRIANGLE_STRIP,  ///< Represents a series of connected triangles, sharing vertices.
                TriangleFan = GL_TRIANGLE_FAN       ///< Represents triangles connected to a central vertex.
            };
        }  // namespace gl
    }      // namespace core
}  // namespace cobalt