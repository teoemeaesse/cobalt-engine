/**
 * @file shader.h
 * @brief Shader class for creating and managing OpenGL shader programs.
 * @author Tomás Marques
 * @date 30-11-2023
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        /**
         * @brief Shader steps that can be added to a shader program.
         */
        enum class ShaderStep {
            Vertex,    ///< Vertex shader.
            Fragment,  ///< Fragment (or pixel) shader.
            Geometry,  ///< Geometry shader.
            Compute    ///< Compute shader.
        };

        /**
         * @brief A shader program. Can be used to render or, in the case of a compute shader, to create parallel programs on the gpu.
         */
        class Shader {
            friend class ShaderBuilder;

            public:
            /**
             * @brief Destroys the shader and frees the shader resources.
             */
            virtual ~Shader();
            /**
             * @brief Copy constructor.
             * @param other The shader to copy.
             * @return The copied shader.
             */
            Shader(const Shader& other) = delete;
            /**
             * @brief Move constructor.
             * @param other The shader to move.
             * @return The moved shader.
             */
            Shader(Shader&& other) noexcept;
            /**
             * @brief Copy assignment operator.
             * @param other The shader to copy.
             * @return The copied shader.
             */
            Shader& operator=(const Shader& other) = delete;
            /**
             * @brief Move assignment operator.
             * @param other The shader to move.
             * @return The moved shader.
             */
            Shader& operator=(Shader&& other) noexcept;

            /**
             * @brief Binds the shader program to the current context.
             */
            void use() const;

            /**
             * @brief Gets the index of a uniform block object with the given name in the shader.
             * @param name The name of the uniform block object.
             * @return The index of the uniform block object.
             */
            const GLuint getUBIndex(const std::string& name) const;
            /**
             * @brief Gets the OpenGL handle to the shader program.
             * @return The OpenGL handle to the shader program.
             */
            const gl::Handle getGLHandle() const;

            /**
             * @brief Sets a uniform integer array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniform1iv(const std::string& name, const GLsizei count, const GLint* value);
            /**
             * @brief Sets a uniform float array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniform1fv(const std::string& name, const GLsizei count, const GLfloat* value);
            /**
             * @brief Sets a uniform integer for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformInt(const std::string& name, const GLint value);
            /**
             * @brief Sets a uniform float for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformFloat(const std::string& name, const GLfloat value);
            /**
             * @brief Sets a uniform vec2 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformVec2(const std::string& name, const glm::vec2& value);
            /**
             * @brief Sets a uniform vec3 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformVec3(const std::string& name, const glm::vec3& value);
            /**
             * @brief Sets a uniform vec4 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformVec4(const std::string& name, const glm::vec4& value);
            /**
             * @brief Sets a uniform vec2 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformVec2v(const std::string& name, const GLsizei count, const glm::vec2* value);
            /**
             * @brief Sets a uniform vec3 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformVec3v(const std::string& name, const GLsizei count, const glm::vec3* value);
            /**
             * @brief Sets a uniform vec4 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformVec4v(const std::string& name, const GLsizei count, const glm::vec4* value);
            /**
             * @brief Sets a uniform mat2 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformMat2(const std::string& name, const glm::mat2& value);
            /**
             * @brief Sets a uniform mat3 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformMat3(const std::string& name, const glm::mat3& value);
            /**
             * @brief Sets a uniform mat4 for the given uniform name.
             * @param name The name of the uniform.
             * @param value The value of the uniform.
             */
            void setUniformMat4(const std::string& name, const glm::mat4& value);
            /**
             * @brief Sets a uniform mat2 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformMat2v(const std::string& name, const GLsizei count, const glm::mat2* value);
            /**
             * @brief Sets a uniform mat3 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformMat3v(const std::string& name, const GLsizei count, const glm::mat3* value);
            /**
             * @brief Sets a uniform mat4 array for the given uniform name.
             * @param name The name of the uniform.
             * @param count The number of elements in the array.
             * @param value The value of the array.
             */
            void setUniformMat4v(const std::string& name, const GLsizei count, const glm::mat4* value);

            private:
            UMap<std::string, GLuint> uniformLocations;  ///< The locations for each uniform.

            /**
             * @brief Gets the location of a uniform with the given name.
             * @param name The name of the uniform.
             * @return The location of the uniform.
             */
            const GLuint getUniformLocation(const std::string& name);

            protected:
            gl::Handle program;  ///< The OpenGL shader program handle.

            /**
             * @brief Creates a new shader program.
             * @param program The OpenGL program handle.
             */
            explicit Shader(const gl::Handle program);

            /**
             * @brief Compiles a shader given its source code.
             * @param shader The shader handle.
             * @param source The source code of the shader.
             */
            static void compile(const gl::Handle shader, const std::string& source);

            /**
             * @brief Links a shader.
             * @param shader The shader handle.
             */
            static void link(const gl::Handle shader);
        };

        /**
         * @brief A builder for shaders. Can be used to create a render, compute or geometry shader, for example.
         */
        class ShaderBuilder {
            public:
            /**
             * @brief Adds a shader step to the shader.
             * @param step The type of shader step to add.
             * @param source The source code of the shader.
             * @return The shader builder.
             */
            ShaderBuilder& addShaderStep(const ShaderStep step, const std::string& source);
            /**
             * @brief Builds a render shader.
             * @return The render shader.
             */
            Shader buildRenderShader() const;
            /**
             * @brief Builds a compute shader.
             * @return The compute shader.
             */
            Shader buildComputeShader() const;

            private:
            UMap<ShaderStep, std::string> sources;  // The shader sources.
        };
    }  // namespace core::gl
}  // namespace cobalt