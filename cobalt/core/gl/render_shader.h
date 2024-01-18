//
// Created
// by
// tomas
// on
// 30-11-2023.
//

#pragma once

#include "core/gl/shader.h"

namespace cobalt {
    namespace core::gl {
        /** @brief: A shader program that can be used to render.
         */
        class RenderShader : public Shader {
            public:
            /** @brief: Creates a new render shader.
             * @param vertexSource: The source code of the vertex shader.
             * @param fragmentSource: The source code of the fragment shader.
             * @return: The render shader.
             */
            RenderShader(std::string& vertexSource, std::string& fragmentSource);
            /** @brief: Creates a new render shader.
             * @param vertexSource: The source code of the vertex shader.
             * @param fragmentSource: The source code of the fragment shader.
             * @param geometrySource: The source code of the geometry shader.v
             * @return: The render shader.
             */
            RenderShader(std::string& vertexSource, std::string& fragmentSource, std::string& geometrySource);
        };
    }  // namespace core
} // namespace cobalt