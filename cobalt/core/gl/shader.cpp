//
// Created by tomas on 30-11-2023.
//

#include "core/gl/shader.h"
#include "core/exceptions/gl_exception.h"
#include "core/gl/render_shader.h"
#include "core/gl/compute_shader.h"


namespace cobalt {
    namespace core {
        Shader::Shader(GLHandle handle) : program(handle) {}

        Shader::~Shader() {
            glDeleteProgram(program);
        }

        void Shader::use() const {
            glUseProgram(program);
        }

        const GLuint Shader::getUBIndex(const std::string& name) const {
            GLuint index = glGetUniformBlockIndex(program, name.c_str());
            if (index == GL_INVALID_INDEX) {
                throw GLException("Uniform block " + name + " not found in shader.");
            }
            return index;
        }

        void Shader::compileShader(const GLHandle shader, const std::string& source) {
            const char* sourcePtr = source.c_str();
            glShaderSource(shader, 1, &sourcePtr, nullptr);
            glCompileShader(shader);
            GLint success;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                GLint logLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                GLchar log[logLength];
                glGetShaderInfoLog(shader, logLength, nullptr, log);
                std::string logString(log);
                throw GLException("Failed to compile shader: " + logString);
            }
        }

        void Shader::linkShader(const GLHandle shader) {
            glLinkProgram(shader);
            GLint success;
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                GLint logLength;
                glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                GLchar log[logLength];
                glGetProgramInfoLog(shader, logLength, nullptr, log);
                std::string logString(log);
                throw GLException("Failed to link shader: " + logString);
            }
        }

        ShaderBuilder& ShaderBuilder::addShaderStep(const ShaderStep step, const std::string& source) {
            sources.insert(std::make_pair(step, source));
            return *this;
        }

        RenderShader ShaderBuilder::buildRenderShader() const {
            std::string vertexSource;
            std::string fragmentSource;
            try {
                std::string vertexSource = sources.at(ShaderStep::Vertex);
                std::string fragmentSource = sources.at(ShaderStep::Fragment);
            } catch (std::out_of_range& e) {
                throw GLException("A render shader must have at least a vertex and a fragment shader source.");
            }
            try {
                std::string geometrySource = sources.at(ShaderStep::Geometry);
                return RenderShader(vertexSource, fragmentSource, geometrySource);
            } catch (std::out_of_range& e) {
                return RenderShader(vertexSource, fragmentSource);
            }
        }

        ComputeShader ShaderBuilder::buildComputeShader() const {
            try {
                std::string computeSource = sources.at(ShaderStep::Compute);
                return ComputeShader(computeSource);
            }
            catch (std::out_of_range& e) {
                throw GLException("A compute shader must have a compute shader source.");
            }
        }
    }
}