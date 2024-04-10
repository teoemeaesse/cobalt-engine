// Created by tomas on
// 02-12-2023

#pragma once

#include "core/gl/texture.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief FrameBuffer Object (FBO). Used for rendering to texture (off-screen
         * rendering and post-processing effects).
         */
        class FBO {
            public:
            struct Attachment {
                gl::TextureEncoding encoding;
                gl::TextureFilter filter = gl::TextureFilters::Linear;
                gl::TextureWrap wrap = gl::TextureWraps::Repeat;
            };

            /**
             * @brief Creates a new FBO with the given buffer attachments.
             * @param width The width of the FBO.
             * @param height The height of the FBO.
             * @param attachments The attachments of the FBO.
             * @return A new FBO.
             */
            FBO(const uint width, const uint height, const Vec<Attachment>& attachments);
            /**
             * @brief Creates a handle to the Default FBO.
             * @return The Default FBO.
             */
            FBO();
            /**
             * @brief Creates a new FBO from an existing FBO.
             * @param other The other FBO.
             * @return The new FBO.
             */
            FBO(const FBO&) = delete;
            /**
             * @brief Moves the FBO.
             * @param other The other FBO.
             * @return The moved FBO.
             */
            FBO(FBO&&) noexcept;
            /**
             * @brief Copy assignment.
             * @param other The other FBO.
             * @return The FBO.
             */
            FBO& operator=(const FBO&) = delete;
            /**
             * @brief Move assignment.
             * @param other The other FBO.
             * @return The FBO.
             */
            FBO& operator=(FBO&&) noexcept;
            /**
             * @brief Destroys the FBO.
             */
            ~FBO();

            /**
             * @brief Resizes the FBO.
             * @param width The new width of the FBO.
             * @param height The new height of the FBO.
             */
            void resize(const uint width, const uint height);
            /**
             * @brief Binds the FBO.
             */
            void bind() const;
            /**
             * @brief Clears the FBO.
             * Must be called after binding the FBO.
             */
            void clear() const;

            /**
             * @brief Sets the color to clear the FBO with.
             * @param color The color to clear the FBO with.
             */
            void setClearColor(const Color& color);

            /**
             * @brief Returns the i-th color texture attached to the FBO.
             * @param i The index of the color texture.
             * @return The texture at the designated color buffer.
             */
            const Opt<Wrap<const Texture2D>> getColorBuffer(uint i) const;
            /**
             * @brief Returns the first color texture attached to the FBO.
             * @return The texture at the first color buffer.
             */
            const Opt<Wrap<const Texture2D>> getColorBuffer() const;
            /**
             * @brief Returns the depth texture attached to the FBO. Optionally returns the depth-stencil texture.
             * @return The depth texture attached to the FBO.
             */
            const Opt<Wrap<const Texture2D>> getDepthBuffer() const;
            /**
             * @brief Returns the stencil texture attached to the FBO. Optionally returns the depth-stencil texture.
             * @return The stencil texture attached to the FBO.
             */
            const Opt<Wrap<const Texture2D>> getStencilBuffer() const;
            /**
             * @brief Returns the width of the FBO.
             * @return The width of the FBO.
             */
            const uint getWidth() const;
            /**
             * @brief Returns the height of the FBO.
             * @return The height of the FBO.
             */
            const uint getHeight() const;

            protected:
            gl::Handle buffer;            // The handle to the FBO.
            Vec<Texture2D> colors;        // The texture attached to the FBO.
            Opt<Texture2D> depth;         // The depth texture attached to the FBO.
            Opt<Texture2D> stencil;       // The stencil texture attached to the FBO.
            Opt<Texture2D> depthStencil;  // The mixed depth and stencil texture attached to the FBO.
            Color clearColor;             // The color to clear the FBO with.
            uint width;                   // The width of the FBO.
            uint height;                  // The height of the FBO.
        };
    }  // namespace core::gl
}  // namespace cobalt