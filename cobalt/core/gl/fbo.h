//
// Created by tomas on 02-12-2023.
//

#pragma once

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
            virtual const uint getWidth() const = 0;
            /* Returns the height of the FBO.
             * @return: The height of the FBO.
             */
            virtual const uint getHeight() const = 0;

            protected:
            Color clearColor;                   // The color to clear the FBO with.
            const GLFramebufferAttachment type; // The type of the texture attached to the FBO.
            
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

            /* Returns the width of the FBO.
             * @return: The width of the FBO.
             */
            const uint getWidth() const override;
            /* Returns the height of the FBO.
             * @return: The height of the FBO.
             */
            const uint getHeight() const override;

            private:
            uint width;     // The width of the FBO.
            uint height;    // The height of the FBO.
        };

        class TargetFBO : public FBO {
            public:
            /* Creates a new FBO with the given width and height.
             * The FBO will have a texture attached to it.
             * @param width: The width of the FBO.
             * @param height: The height of the FBO.
             * @param format: The format of the texture attached to the FBO.
             * @param encoding: The encoding of the texture attached to the FBO.
             * @return: A new FBO.
             */
            TargetFBO(const uint width, const uint height,
                      const GLFramebufferAttachment type = GLFramebufferAttachment::Color,
                      const GLTextureFormat format = GLTextureFormat::RGBA,
                      const GLTextureEncoding encoding = GLTextureEncoding::RGBA8);
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

            /* Returns the texture attached to the FBO.
             * @return: The texture attached to the FBO.
             */
            const Texture& getTexture() const;
            /* Returns the width of the FBO.
             * @return: The width of the FBO.
             */
            const uint getWidth() const override;
            /* Returns the height of the FBO.
             * @return: The height of the FBO.
             */
            const uint getHeight() const override;

            private:
            GLHandle buffer;    // The FBO handle.
            Texture texture;    // The texture attached to the FBO.
        };
    }
}