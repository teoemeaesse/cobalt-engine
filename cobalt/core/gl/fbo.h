//
// Created by tomas on 02-12-2023.
//

#pragma once

#include <optional>

#include "core/gl/texture.h"
#include "core/gfx/color.h"


namespace cobalt {
    namespace core {
        /* FrameBuffer Object (FBO). Used for rendering to texture (off-screen rendering
         * and post-processing effects).
         */
        class FBO {
            public:
            /* Destroys the FBO.
             */
            ~FBO() = default;

            /* Resizes the FBO.
             * @param width: The new width of the FBO.
             * @param height: The new height of the FBO.
             */
            virtual void resize(const uint width, const uint height) = 0;
            /* Binds the FBO.
             */
            virtual void bind() const = 0;
            /* Clears the FBO.
             * Must be called after binding the FBO.
             */
            void clear() const;

            /* Sets the color to clear the FBO with.
             * @param color: The color to clear the FBO with.
             */
            void setClearColor(const Color& color);

            /* Returns the width of the FBO.
             * @return: The width of the FBO.
             */
            const uint getWidth() const;
            /* Returns the height of the FBO.
             * @return: The height of the FBO.
             */
            const uint getHeight() const;

            protected:
            Color clearColor;                   // The color to clear the FBO with.
            const GLFramebufferAttachment type; // The type of the texture attached to the FBO.
            uint width;                         // The width of the FBO.
            uint height;                        // The height of the FBO.
            
            /* Creates a new FBO with the given width and height.
             * The FBO will have a texture attached to it.
             * @param type: The type of the texture attached to the FBO.
             * @return: A new FBO.
             */
            FBO(const GLFramebufferAttachment type);
        };

        class DefaultFBO : public FBO {
            public:
            /* Creates a new default FBO.
             * @param type: The type of the texture attached to the FBO.
             * @return: A new default FBO.
             */
            DefaultFBO(const GLFramebufferAttachment type = GLFramebufferAttachment::Color);
            /* Destroys the FBO.
             */
            ~DefaultFBO() = default;
            
            /* Resizes the FBO.
             * @param width: The new width of the FBO.
             * @param height: The new height of the FBO.
             */
            void resize(const uint width, const uint height) override;
            /* Binds the FBO.
             */
            void bind() const override;
        };

        class TargetFBO : public FBO {
            public:
            /* Creates a new FBO with the given width and height.
             * The FBO will have a texture attached to it.
             * @param width: The width of the FBO.
             * @param height: The height of the FBO.
             * @param type: The type of the texture attached to the FBO.
             * @return: A new FBO.
             */
            TargetFBO(const uint width, const uint height,
                      const GLFramebufferAttachment type = GLFramebufferAttachment::Color,
                      const GLTextureFilter filter = GLTextureFilter::Linear,
                      const GLTextureWrap wrap = GLTextureWrap::ClampToEdge,
                      const bool srgb = false);
            /* Destroys the FBO.
            */
            ~TargetFBO();

            /* Resizes the FBO.
             * @param width: The new width of the FBO.
             * @param height: The new height of the FBO.
             */
            void resize(const uint width, const uint height) override;
            /* Binds the FBO.
             */
            void bind() const override;

            /* Returns whether the FBO has this attachment.
             * @param attachment: The attachment to check for.
             * @return: Whether the FBO has this attachment.
             */
            const bool hasAttachment(const GLFramebufferAttachment attachment) const;
            /* Returns the texture attached to the FBO.
             * @return: The texture attached to the FBO.
             */
            const Texture& getColorBuffer() const;
            /* Returns the depth texture attached to the FBO.
             * @return: The depth texture attached to the FBO.
             */
            const Texture& getDepthBuffer() const;
            /* Returns the stencil texture attached to the FBO.
             * @return: The stencil texture attached to the FBO.
             */
            const Texture& getStencilBuffer() const;

            private:
            GLHandle buffer;                        // The FBO handle.
            std::optional<Texture2D> color;         // The texture attached to the FBO.
            std::optional<Texture2D> depthStencil;  // The depth and/or stencil texture attached to the FBO.
        };
    }
}