//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/pch.h"


namespace cobalt {
    namespace core {
        enum class ShaderStep {
            Vertex,
            Fragment,
            Geometry,
            Compute
        };

        /** A shader program. Can be used to render, compute, etc.
        */
        class Shader {
            friend class ShaderBuilder;

            public:
            /** Destroys the shader program.
            */
            virtual ~Shader();
            /** Copy constructor.
             * @param other: The shader to copy.
             * @return: The copied shader.
             */
            Shader(const Shader& other) = delete;
            /** Move constructor.
             * @param other: The shader to move.
             * @return: The moved shader.
             */
            Shader(Shader&& other) noexcept;
            /** Copy assignment operator.
             * @param other: The shader to copy.
             * @return: The copied shader.
             */
            Shader& operator=(const Shader& other) = delete;
            /** Move assignment operator.
             * @param other: The shader to move.
             * @return: The moved shader.
             */
            Shader& operator=(Shader&& other) noexcept;

            /** Binds the shader program.
            */
            void use() const;
            /** Gets the index of a uniform block object with the given name in the shader.
             * @param name: The name of the uniform block object.
             * @return: The index of the uniform block object.
             */
            const GLuint getUBIndex(const std::string& name) const;
            /** Gets the opengl program handle.
             * @return: The opengl program handle.
             */
            const GLHandle getGLHandle() const;

            /** Sets a uniform integer array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniform1iv(const std::string& name, const GLsizei count, const GLint* value);
            /** Sets a uniform float array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniform1fv(const std::string& name, const GLsizei count, const GLfloat* value);
            /** Sets a uniform integer for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformInt(const std::string& name, const GLint value);
            /** Sets a uniform float for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformFloat(const std::string& name, const GLfloat value);
            /** Sets a uniform vec2 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformVec2(const std::string& name, const glm::vec2& value);
            /** Sets a uniform vec3 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformVec3(const std::string& name, const glm::vec3& value);
            /** Sets a uniform vec4 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformVec4(const std::string& name, const glm::vec4& value);
            /** Sets a uniform vec2 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformVec2v(const std::string& name, const GLsizei count, const glm::vec2* value);
            /** Sets a uniform vec3 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformVec3v(const std::string& name, const GLsizei count, const glm::vec3* value);
            /** Sets a uniform vec4 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformVec4v(const std::string& name, const GLsizei count, const glm::vec4* value);
            /** Sets a uniform mat2 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformMat2(const std::string& name, const glm::mat2& value);
            /** Sets a uniform mat3 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformMat3(const std::string& name, const glm::mat3& value);
            /** Sets a uniform mat4 for the given uniform name.
             * @param name: The name of the uniform.
             * @param value: The value of the uniform.
             */
            void setUniformMat4(const std::string& name, const glm::mat4& value);
            /** Sets a uniform mat2 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformMat2v(const std::string& name, const GLsizei count, const glm::mat2* value);
            /** Sets a uniform mat3 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformMat3v(const std::string& name, const GLsizei count, const glm::mat3* value);
            /** Sets a uniform mat4 array for the given uniform name.
             * @param name: The name of the uniform.
             * @param count: The number of elements in the array.
             * @param value: The value of the array.
             */
            void setUniformMat4v(const std::string& name, const GLsizei count, const glm::mat4* value);
            

            private:
            UMap<std::string, GLuint> uniformLocations;   // The uniform block indices.

            /** Gets the location of a uniform with the given name.
             * @param name: The name of the uniform.
             * @return: The location of the uniform.
             */
            const GLuint getUniformLocation(const std::string& name);

            protected:
            GLHandle program;   // The opengl program handle.
            
            /** Creates a new shader program.
            * @param program: The opengl program handle.
            */
            Shader(const GLHandle program);

            /** Compiles a shader given its source code.
             * @param shader: The shader handle.
             * @param source: The source code of the shader.
             */
            static void compileShader(const GLHandle shader, const std::string& source);
            /** Links a shader.
             * @param shader: The shader handle.
             */
            static void linkShader(const GLHandle shader);
        };

        class RenderShader;
        class ComputeShader;

        /** A builder for shaders. Can be used to create a render, compute or geometry shader, for example.
        */
        class ShaderBuilder {
            public:
            /** Adds a shader step to the shader.
            * @param step: The type of shader step to add.
            * @param source: The source code of the shader.
            * @return: The shader builder.
            */
            ShaderBuilder& addShaderStep(const ShaderStep step, const std::string& source);
            /** Builds a render shader.
             * @return: The render shader.
             */
            RenderShader buildRenderShader() const;
            /** Builds a compute shader.
             * @return: The compute shader.
             */
            ComputeShader buildComputeShader() const;

            private:
            UMap<ShaderStep, std::string> sources;  // The shader sources.
        };
    }
}