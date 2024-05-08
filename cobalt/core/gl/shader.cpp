/**
 * @file shader.cpp
 * @brief Shader class for creating and managing OpenGL shader programs.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#include "core/gl/shader.h"

#include "core/exception.h"

namespace cobalt {
    namespace core::gl {
        Shader::Shader(gl::Handle handle) : program(handle) {}

        Shader::~Shader() {
            if (program != 0) {
                glDeleteProgram(program);
            }
        }

        Shader::Shader(Shader&& other) noexcept : program(other.program), uniformLocations(other.uniformLocations) { other.program = 0; }

        Shader& Shader::operator=(Shader&& other) noexcept {
            program = other.program;
            uniformLocations = other.uniformLocations;
            other.program = 0;
            return *this;
        }

        void Shader::use() const { glUseProgram(program); }

        const GLuint Shader::getUBIndex(const std::string& name) const {
            GLuint index = glGetUniformBlockIndex(program, name.c_str());
            if (index == GL_INVALID_INDEX) {
                throw CoreException<Shader>("Uniform block " + name + " not found in shader");
            }
            return index;
        }

        const gl::Handle Shader::getGLHandle() const { return program; }

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

        void Shader::setUniformInt(const std::string& name, const GLint value) { glUniform1i(getUniformLocation(name), value); }

        void Shader::setUniformFloat(const std::string& name, const GLfloat value) { glUniform1f(getUniformLocation(name), value); }

        void Shader::setUniformVec2(const std::string& name, const glm::vec2& value) { glUniform2f(getUniformLocation(name), value.x, value.y); }

        void Shader::setUniformVec3(const std::string& name, const glm::vec3& value) {
            glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
        }

        void Shader::setUniformVec4(const std::string& name, const glm::vec4& value) {
            glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
        }

        void Shader::setUniformVec2v(const std::string& name, const GLsizei count, const glm::vec2* value) {
            glUniform2fv(getUniformLocation(name), count, (GLfloat*)value);
        }

        void Shader::setUniformVec3v(const std::string& name, const GLsizei count, const glm::vec3* value) {
            glUniform3fv(getUniformLocation(name), count, (GLfloat*)value);
        }

        void Shader::setUniformVec4v(const std::string& name, const GLsizei count, const glm::vec4* value) {
            glUniform4fv(getUniformLocation(name), count, (GLfloat*)value);
        }

        void Shader::setUniformMat2(const std::string& name, const glm::mat2& value) {
            glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*)&value);
        }

        void Shader::setUniformMat3(const std::string& name, const glm::mat3& value) {
            glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*)&value);
        }

        void Shader::setUniformMat4(const std::string& name, const glm::mat4& value) {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (GLfloat*)&value);
        }

        void Shader::setUniformMat2v(const std::string& name, const GLsizei count, const glm::mat2* value) {
            glUniformMatrix2fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*)value);
        }

        void Shader::setUniformMat3v(const std::string& name, const GLsizei count, const glm::mat3* value) {
            glUniformMatrix3fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*)value);
        }

        void Shader::setUniformMat4v(const std::string& name, const GLsizei count, const glm::mat4* value) {
            glUniformMatrix4fv(getUniformLocation(name), count, GL_FALSE, (GLfloat*)value);
        }

        void Shader::compile(const gl::Handle shader, const std::string& source) {
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
                throw CoreException<Shader>("Failed to compile shader: " + logString);
            }
        }

        void Shader::link(const gl::Handle shader) {
            glLinkProgram(shader);
            GLint success;
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                GLint logLength;
                glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                GLchar log[logLength];
                glGetProgramInfoLog(shader, logLength, nullptr, log);
                std::string logString(log);
                throw CoreException<Shader>("Failed to link shader: " + logString);
            }
        }

        ShaderBuilder& ShaderBuilder::addShaderStep(const ShaderStep step, const std::string& source) {
            sources.insert(std::make_pair(step, source));
            return *this;
        }

        Shader ShaderBuilder::buildRenderShader() const {
            gl::Handle vertexShader = 0, fragmentShader = 0, geometryShader = 0;
            gl::Handle program = glCreateProgram();
            try {
                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                Shader::compile(vertexShader, sources.at(ShaderStep::Vertex));
                Shader::compile(fragmentShader, sources.at(ShaderStep::Fragment));
                glAttachShader(program, vertexShader);
                glAttachShader(program, fragmentShader);
            } catch (std::out_of_range& e) {
                throw CoreException<Shader>("A render shader must have at least a vertex and a fragment shader source");
            }
            try {
                geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
                Shader::compile(geometryShader, sources.at(ShaderStep::Geometry));
                glAttachShader(program, geometryShader);
            } catch (std::out_of_range& e) {
                // No geometry shader
            }
            glValidateProgram(program);
            Shader::link(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            if (geometryShader != 0) glDeleteShader(geometryShader);

            return Shader(program);
        }

        Shader ShaderBuilder::buildComputeShader() const {
            gl::Handle computeShader = 0;
            gl::Handle program = glCreateProgram();
            try {
                computeShader = glCreateShader(GL_COMPUTE_SHADER);
                Shader::compile(computeShader, sources.at(ShaderStep::Compute));
                glAttachShader(program, computeShader);
            } catch (std::out_of_range& e) {
                throw CoreException<Shader>("A compute shader must have a compute shader source");
            }
            glValidateProgram(program);
            Shader::link(program);
            glDeleteShader(computeShader);

            return Shader(program);
        }
    }  // namespace core::gl
}  // namespace cobalt