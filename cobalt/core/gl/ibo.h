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
             * @param indexCount: The number of indices.
             * @return: IBO.
             */
            IBO(const GLUsage usage, const uint indexCount);
            /* Creates an index buffer object with the given data.
             * @param usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
             * @param data: The data.
             * @param indexCount: The number of indices.
             */
            IBO(const GLUsage usage, const uint* data, const uint indexCount);
            /* Destroys the IBO.
             */
            ~IBO();
            /* Copy constructor.
             * @param other: The IBO to copy.
             * @return: IBO.
             */
            IBO(const IBO&) = delete;
            /* Move constructor.
             * @param ibo: The IBO to move.
             * @return: IBO.
             */
            IBO(IBO&&) noexcept;
            /* Copy assignment operator.
             * @param other: The IBO to copy.
             * @return: IBO.
             */
            IBO& operator=(const IBO&) = delete;
            /* Move assignment operator.
             * @param other: The IBO to move.
             * @return: IBO.
             */
            IBO& operator=(IBO&&) noexcept;

            /* Binds the IBO to the current context.
             */
            void bind() const;
            /* Unbinds the IBO from the current context.
             */
            void unbind() const;
            /* Get the number of indices.
             * @return: The number of indices.
             */
            const uint getCount() const;

            /* Create an IBO for n quads.
             * @param usage: The usage of the buffer.
             * @param count: The number of quads.
             */
            static IBO fromQuads(const GLUsage usage, const uint count);

            private:
            GLHandle buffer;        // The opengl buffer handle.
            GLUsage usage;          // The usage of the buffer.
            uint indexCount;        // The number of indices.
        };
    }
}