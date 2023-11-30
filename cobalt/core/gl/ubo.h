//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/types/types.h"
#include "core/gl/definitions.h"


namespace cobalt {
    /* A uniform buffer object. Used to store uniform data
     * that is shared between multiple shaders.
     */
    class UBO {
        public:
        /* Creates a uniform buffer object.
         * @param usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, GL_STREAM_DRAW.
         * @param size: The size of the buffer in bytes.
         * @return: UBO.
         */
        UBO(const GLUsage usage, const size_t size);
        /* Destroys the UBO.
         */
        ~UBO();

        /* Binds the UBO to the current context.
         */
        void bind() const;
        /* Unbinds the UBO from the current context.
         */
        void unbind() const;
        /* Binds the UBO to a shader binding point. Bind before calling.
         * @param shader: The shader to bind to.
         * @param bindingPoint: The binding point to bind to.
         */
        void setBindingPoint(const GLHandle shader, const GLHandle bindingPoint) const;
        /* Sets the data of the entire buffer. Bind before calling.
         * @param data: The data to load.
         * @param size: The size of the data in bytes.
         */
        void load(const void* data, const size_t size) const;
        /* Sets the data of a specific uniform or uniform block. Bind before calling.
         * @param data: The data to load.
         * @param size: The size of the data in bytes.
         * @param offset: The offset in bytes from the start of the buffer.
         */
        void load(const void* data, const size_t size, const size_t offset) const;

        private:
        GLHandle buffer;        // The opengl buffer handle.
        const GLUsage usage;    // The usage of the buffer.
        const size_t size;      // The size of the buffer in bytes.  
    };
}