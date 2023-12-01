//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/gl/shader.h"


namespace cobalt {
    namespace core {
        /* A compute shader program.
         */
        class ComputeShader : public Shader {
            friend class ShaderBuilder;
            
            private:
            /* Creates a new compute shader.
             * @param computeSource: The source code of the compute shader.
             * @return: The compute shader.
             */
            ComputeShader(std::string& computeSource);
        };
    }
}