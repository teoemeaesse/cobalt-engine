// Created by tomas on
// 30-11-2023

#pragma once

#include "core/gl/shader.h"

namespace cobalt {
    namespace core::gl {
        /** @brief: A compute shader program.
         */
        class ComputeShader : public Shader {
            public:
            /** @brief: Creates a new compute shader.
             * @param computeSource: The source code of the compute shader.
             * @return: The compute shader.
             */
            ComputeShader(std::string& computeSource);
        };
    }  // namespace core::gl
}  // namespace cobalt