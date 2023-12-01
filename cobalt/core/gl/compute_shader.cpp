//
// Created by tomas on 30-11-2023.
//

#include "core/gl/compute_shader.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace core {
        ComputeShader::ComputeShader(std::string& computeSource) : Shader(glCreateProgram()) {
            CB_CORE_INFO("Compiling compute shader...");
            GLHandle computeShader = glCreateShader(GL_COMPUTE_SHADER);
            const char* computeSourcePtr = computeSource.c_str();
            glShaderSource(computeShader, 1, &computeSourcePtr, NULL);
            compileShader(computeShader, computeSource);
            CB_CORE_INFO("Linking compute shader...");
            glAttachShader(program, computeShader);
            glValidateProgram(program);
            linkShader(program);
            glDeleteShader(computeShader);
        }
    }
}