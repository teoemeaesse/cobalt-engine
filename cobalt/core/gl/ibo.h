//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/utils/types.h"
#include "core/gl/definitions.h"


namespace cobalt {
    namespace core {
        /* Index buffer object, used for indexed rendering.
        */
        class IBO {
            public:
            /* Creates an index buffer object.
            * @param usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
            * @return: IBO.
            */
            IBO(const GLUsage usage);
            /* Destroys the IBO.
            */
            ~IBO();

            /* Binds the IBO to the current context.
            */
            void bind() const;
            /* Unbinds the IBO from the current context.
            */
            void unbind() const;
            /* Fills the IBO with quad indices.
            * @param count: The number of quads to render.
            */
            void quads(const uint count) const;

            private:
            GLHandle buffer;        // The opengl buffer handle.
            const GLUsage usage;    // The usage of the buffer.
        };
    }
}