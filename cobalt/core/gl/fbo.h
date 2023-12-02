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
            /* Creates a new FBO with the given width and height.
             * The FBO will have a texture attached to it.
             * @param width: The width of the FBO.
             * @param height: The height of the FBO.
             * @param type: The type of the texture attached to the FBO.
             * @param format: The format of the texture attached to the FBO.
             * @return: A new FBO.
             */
            FBO(const uint width, const uint height, const GLFramebufferAttachment type, const GLTextureFormat format);
            /* Creates a new default FBO with the given width and height.
             * This is the FBO that is used by the window and displayed on the screen.
             * @param width: The width of the FBO.
             * @param height: The height of the FBO.
             */
            FBO(const uint width, const uint height);
            /* Destroys the FBO.
             */
            ~FBO();

            /* Binds the FBO.
             */
            void bind() const;
            /* Unbinds the FBO.
             */
            void unbind() const;
            /* Resizes the FBO.
             * @param width: The new width of the FBO.
             * @param height: The new height of the FBO.
             */
            void resize(const uint width, const uint height);
            /* Clears the FBO.
             */
            void clear();

            /* Sets the color to clear the FBO with.
             * @param color: The color to clear the FBO with.
             */
            inline void setClearColor(const Color& color) { clearColor = color; }

            /* Returns the texture attached to the FBO.
             * @return: The texture attached to the FBO.
             */
            inline const Texture& getTexture() const { return texture; }
            /* Returns the width of the FBO.
             * @return: The width of the FBO.
             */
            inline uint getWidth() const { return texture.getWidth(); }
            /* Returns the height of the FBO.
             * @return: The height of the FBO.
             */
            inline uint getHeight() const { return texture.getHeight(); }

            private:
            GLHandle buffer;                    // The FBO handle.
            Texture texture;                    // The texture attached to the FBO.
            Color clearColor;                   // The color to clear the FBO with.
            const GLFramebufferAttachment type; // The type of the texture attached to the FBO.
        };
    }
}