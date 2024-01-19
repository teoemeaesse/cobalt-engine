// Created by tomas on
// 30-11-2023

#include "core/gl/render_shader.h"

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        RenderShader::RenderShader(std::string& vertexSource, std::string& fragmentSource) : Shader(glCreateProgram()) {
            CB_CORE_INFO("Compiling render shader...");
            gl::Handle vertexShader = glCreateShader(GL_VERTEX_SHADER);
            gl::Handle fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            const char* vertexSourcePtr = vertexSource.c_str();
            const char* fragmentSourcePtr = fragmentSource.c_str();
            glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
            glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
            compileShader(vertexShader, vertexSource);
            compileShader(fragmentShader, fragmentSource);
            CB_CORE_INFO("Linking render shader...");
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glValidateProgram(program);
            linkShader(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        RenderShader::RenderShader(std::string& vertexSource, std::string& fragmentSource, std::string& geometrySource) : Shader(glCreateProgram()) {
            CB_CORE_INFO("Compiling render shader...");
            gl::Handle vertexShader = glCreateShader(GL_VERTEX_SHADER);
            gl::Handle fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            gl::Handle geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            const char* vertexSourcePtr = vertexSource.c_str();
            const char* fragmentSourcePtr = fragmentSource.c_str();
            const char* geometrySourcePtr = geometrySource.c_str();
            glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
            glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
            glShaderSource(geometryShader, 1, &geometrySourcePtr, NULL);
            compileShader(vertexShader, vertexSource);
            compileShader(fragmentShader, fragmentSource);
            compileShader(geometryShader, geometrySource);
            CB_CORE_INFO("Linking render shader...");
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glAttachShader(program, geometryShader);
            glValidateProgram(program);
            linkShader(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteShader(geometryShader);
        }
    }  // namespace core::gl
}  // namespace cobalt