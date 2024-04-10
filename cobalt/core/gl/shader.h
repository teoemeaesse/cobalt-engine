// Created by tomas on
// 30-11-2023

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::gl {
        enum class ShaderStep { Vertex, Fragment, Geometry, Compute };

        /**
         * @brief A shader program. Can be used to render, compute, etc.
         */
        class Shader {
            friend class ShaderBuilder;

            public:
            /**
             * @brief Destroys the shader program.
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
             * @brief Binds the shader program.
             */
            void use() const;
            /**
             * @brief Gets the index of a uniform block object with the given name in the
             * shader.
             * @param name The name of the uniform block object.
             * @return The index of the uniform block object.
             */
            const GLuint getUBIndex(const std::string& name) const;
            /**
             * @brief Gets the OpenGL program handle.
             * @return The OpenGL program handle.
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
            UMap<std::string,
                 GLuint> uniformLocations;  // The uniform block indices.

            /**
             * @brief Gets the location of a uniform with the given name.
             * @param name The name of the uniform.
             * @return The location of the uniform.
             */
            const GLuint getUniformLocation(const std::string& name);

            protected:
            gl::Handle program;  // The OpenGL program handle.

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
            static void compileShader(const gl::Handle shader, const std::string& source);
            /**
             * @brief Links a shader.
             * @param shader The shader handle.
             */
            static void linkShader(const gl::Handle shader);
        };

        /**
         * @brief A shader program that can be used to render.
         */
        class RenderShader : public Shader {
            public:
            /**
             * @brief Creates a new render shader.
             * @param vertexSource The source code of the vertex shader.
             * @param fragmentSource The source code of the fragment shader.
             * @return The render shader.
             */
            RenderShader(std::string& vertexSource, std::string& fragmentSource);
            /**
             * @brief Creates a new render shader.
             * @param vertexSource The source code of the vertex shader.
             * @param fragmentSource The source code of the fragment shader.
             * @param geometrySource The source code of the geometry shader.v
             * @return The render shader.
             */
            RenderShader(std::string& vertexSource, std::string& fragmentSource, std::string& geometrySource);
        };
        /**
         * @brief A shader program that can be used to compute.
         */
        class ComputeShader : public Shader {
            public:
            /**
             * @brief Creates a new compute shader.
             * @param computeSource The source code of the compute shader.
             * @return The compute shader.
             */
            ComputeShader(std::string& computeSource);
        };

        /**
         * @brief A builder for shaders. Can be used to create a render, compute or geometry
         * shader, for example.
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
            RenderShader buildRenderShader() const;
            /**
             * @brief Builds a compute shader.
             * @return The compute shader.
             */
            ComputeShader buildComputeShader() const;

            private:
            UMap<ShaderStep, std::string> sources;  // The shader sources.
        };
    }  // namespace core::gl
}  // namespace cobalt