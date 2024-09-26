/**
 * @file fbo.h
 * @brief Frame Buffer Object (FBO) class for rendering.
 * @author Tomás Marques
 * @date 02-12-2023
 */

#pragma once

#include "core/gl/texture.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief A Frame Buffer Object (FBO) holds shader output data in one or more attachments and is used for live or off-screen rendering.
         * This class manages the resources associated with frame buffers, including texture attachments and clearing mechanisms.
         */
        class FBO {
            public:
            /**
             * @brief Configuration for a GL texture attachment in an FBO.
             * This structure holds the settings used for texture attachments to the FBO, defining how textures should be encoded, filtered, and
             * wrapped.
             */
            struct Attachment {
                gl::TextureEncoding encoding;                           ///< Encoding format of the texture.
                gl::TextureFilter filter = gl::TextureFilters::Linear;  ///< Filtering mode of the texture, defaults to Linear.
                gl::TextureWrap wrap = gl::TextureWraps::Repeat;        ///< Wrapping mode of the texture, defaults to Repeat.
            };

            /**
             * @brief Constructs an FBO with specific dimensions and attachments.
             * @param width The width of the FBO in pixels.
             * @param height The height of the FBO in pixels.
             * @param attachments A vector of Attachment objects specifying the configuration for each attachment.
             */
            FBO(const uint width, const uint height, const std::vector<Attachment>& attachments);
            /**
             * @brief Constructs the default FBO, typically representing the screen.
             */
            FBO();
            /**
             * @brief Destroys the FBO and cleans up its OpenGL resources.
             */
            ~FBO();
            /**
             * @brief Copy constructor is deleted to prevent copying of FBO resources.
             */
            FBO(const FBO&) = delete;
            /**
             * @brief Move constructor to transfer ownership of FBO resources.
             * @param other The other FBO to move.
             */
            FBO(FBO&&) noexcept;
            /**
             * @brief Copy assignment is deleted to prevent copying of FBO resources.
             */
            FBO& operator=(const FBO&) = delete;
            /**
             * @brief Move assignment operator to transfer ownership of FBO resources.
             * @param other The other FBO to move.
             */
            FBO& operator=(FBO&&) noexcept;

            /**
             * @brief Resizes the FBO to new dimensions.
             * @param width The new width of the FBO in pixels.
             * @param height The new height of the FBO in pixels.
             */
            void resize(const uint width, const uint height);

            /**
             * @brief Binds this FBO to the current context.
             */
            void bind() const;

            /**
             * @brief Clears the FBO contents. This function must be called after binding the FBO.
             */
            void clear() const;

            /**
             * @brief Sets the clear color for the FBO.
             * @param color The color used to clear the FBO.
             */
            void setClearColor(const Color& color);

            /**
             * @brief Retrieves a specific color texture attached to the FBO.
             * @param i The index of the color texture to retrieve.
             * @return An optional wrapper around the requested texture, empty if not available.
             */
            const std::optional<std::reference_wrapper<const Texture2D>> getColorBuffer(uint i) const;
            /**
             * @brief Retrieves the first color texture attached to the FBO.
             * @return An optional wrapper around the first texture, empty if not available.
             */
            const std::optional<std::reference_wrapper<const Texture2D>> getColorBuffer() const;
            /**
             * @brief Retrieves the depth texture attached to the FBO, which may also include the depth-stencil texture.
             * @return An optional wrapper around the depth texture, empty if not available.
             */
            const std::optional<std::reference_wrapper<const Texture2D>> getDepthBuffer() const;
            /**
             * @brief Retrieves the stencil texture attached to the FBO, which may also include the depth-stencil texture.
             * @return An optional wrapper around the stencil texture, empty if not available.
             */
            const std::optional<std::reference_wrapper<const Texture2D>> getStencilBuffer() const;

            /**
             * @brief Gets the width of the FBO.
             * @return The width of the FBO in pixels.
             */
            const uint getWidth() const;
            /**
             * @brief Gets the height of the FBO.
             * @return The height of the FBO in pixels.
             */
            const uint getHeight() const;

            protected:
            gl::Handle buffer;                      ///< OpenGL handle to the FBO.
            std::vector<Texture2D> colors;          ///< Textures attached to color buffers of the FBO.
            std::optional<Texture2D> depth;         ///< Optional texture attached to the depth buffer.
            std::optional<Texture2D> stencil;       ///< Optional texture attached to the stencil buffer.
            std::optional<Texture2D> depthStencil;  ///< Optional texture that serves both as depth and stencil buffer.
            Color clearColor;                       ///< Color used to clear the FBO.
            uint width;                             ///< Width of the FBO.
            uint height;                            ///< Height of the FBO.
        };

    }  // namespace core::gl
}  // namespace cobalt