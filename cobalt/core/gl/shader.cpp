//
// Created by tomas on 30-11-2023.
//

#include "core/gl/render_shader.h"
#include "core/gl/compute_shader.h"
#include "core/pch.h"


namespace cobalt {
    namespace core {
        Shader::Shader(GLHandle handle) : program(handle) {
        }

        Shader::~Shader() {
            if (program != 0) {
                glDeleteProgram(program);
            }
        }

        Shader::Shader(Shader&& other) noexcept :
            program(other.program),
            uniformLocations(other.uniformLocations)
        {
            other.program = 0;
        }

        Shader& Shader::operator=(Shader&& other) noexcept {
            program = other.program;
            uniformLocations = other.uniformLocations;
            other.program = 0;
            return *this;
        }

        void Shader::use() const {
            glUseProgram(program);
        }

        const GLuint Shader::getUBIndex(const std::string& name) const {
            GLuint index = glGetUniformBlockIndex(program, name.c_str());
            if (index == GL_INVALID_INDEX) {
                throw GLException("Uniform block " + name + " not found in shader");
            }
            return index;
        }

        const GLHandle Shader::getGLHandle() const {
            return program;
        }
        
        const GLuint Shader::getUniformLocation(const std::string& name) {
            GLint linkStatus;
            try {
                return uniformLocations.at(name);
            } catch (std::out_of_range& e) {
                GLuint location = glGetUniformLocation(program, name.c_str());
                if (location == GL_INVALID_INDEX) {
                    CB_CORE_WARN("Uniform {0} not found in shader", name);
                }
                uniformLocations.insert(std::make_pair(name, location));
                return location;
            }
        }

        void Shader::setUniform1iv(const std::string& name, const GLsizei count, const GLint* value) {
            glUniform1iv(getUniformLocation(name), count, value);
        }

        void Shader::setUniform1fv(const std::string& name, const GLsizei count, const GLfloat* value) {
            glUniform1fv(getUniformLocation(name), count, value);
        }

        void Shader::setUniformInt(const std::string& name, const GLint value) {
            glUniform1i(getUniformLocation(name), value);
        }

        void Shader::setUniformFloat(const std::string& name, const GLfloat value) {
            glUniform1f(getUniformLocation(name), value);
        }

        void Shader::setUniformVec2(const std::string& name, const glm::vec2& value) {
            glUniform2f(getUniformLocation(name), value.x, value.y);
        }

        void Shader::setUniformVec3(const std::string& name, const glm::vec3& value) {
            glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
        }

        void Shader::setUniformVec4(const std::string& name, const glm::vec4& value) {
            glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
        }

        void Shader::setUniformVec2v(const std::string& name, const GLsizei count, const glm::vec2* value) {
            glUniform2fv(getUniformLocation(name), count, (GLfloat*) value);
        }

        void Shader::setUniformVec3v(const std::string& name, const GLsizei count, const glm::vec3* value) {
            glUniform3fv(getUniformLocation(name), count, (GLfloat*) value);
        }

        void Shader::setUniformVec4v(const std::string& name, const GLsizei count, const glm::vec4* value) {
            glUniform4fv(getUniformLocation(name), count, (GLfloat*) value);
        }

        void Shader::setUniformMat2(const std::string& name, const glm::mat2& value) {
            glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*) &value);
        }

        void Shader::setUniformMat3(const std::string& name, const glm::mat3& value) {
            glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*) &value);
        }

        void Shader::setUniformMat4(const std::string& name, const glm::mat4& value) {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*) &value);
        }

        void Shader::setUniformMat2v(const std::string& name, const GLsizei count, const glm::mat2* value) {
            glUniformMatrix2fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*) value);
        }

        void Shader::setUniformMat3v(const std::string& name, const GLsizei count, const glm::mat3* value) {
            glUniformMatrix3fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*) value);
        }

        void Shader::setUniformMat4v(const std::string& name, const GLsizei count, const glm::mat4* value) {
            glUniformMatrix4fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*) value);
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
                vertexSource = sources.at(ShaderStep::Vertex);
                fragmentSource = sources.at(ShaderStep::Fragment);
            } catch (std::out_of_range& e) {
                throw GLException("A render shader must have at least a vertex and a fragment shader source");
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
                throw GLException("A compute shader must have a compute shader source");
            }
        }
    }
}