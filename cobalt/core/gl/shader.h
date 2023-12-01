//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/types/types.h"
#include "core/gl/definitions.h"


namespace cobalt {
    namespace core {
        enum class ShaderStep {
            Vertex,
            Fragment,
            Geometry,
            Compute
        };

        /* A shader program. Can be used to render, compute, etc.
        */
        class Shader {
            friend class ShaderBuilder;

            public:
            /* Destroys the shader program.
            */
            virtual ~Shader();

            /* Binds the shader program.
            */
            void use() const;
            /* Gets the index of a uniform block object with the given name in the shader.
             * @param name: The name of the uniform block object.
             * @return: The index of the uniform block object.
             */
            const GLuint getUBIndex(const std::string& name) const;

            protected:
            const GLHandle program;   // The opengl program handle.

            /* Creates a new shader program.
            * @param program: The opengl program handle.
            */
            Shader(const GLHandle program);
            
            /* Compiles a shader given its source code.
             * @param shader: The shader handle.
             * @param source: The source code of the shader.
             */
            static void compileShader(const GLHandle shader, const std::string& source);
            /* Links a shader.
             * @param shader: The shader handle.
             */
            static void linkShader(const GLHandle shader);
        };

        class RenderShader;
        class ComputeShader;

        /* A builder for shaders. Can be used to create a render, compute or geometry shader, for example.
        */
        class ShaderBuilder {
            public:

            /* Adds a shader step to the shader.
            * @param step: The type of shader step to add.
            * @param source: The source code of the shader.
            * @return: The shader builder.
            */
            ShaderBuilder& addShaderStep(const ShaderStep step, const std::string& source);
            /* Builds a render shader.
             * @return: The render shader.
             */
            RenderShader buildRenderShader() const;
            /* Builds a compute shader.
             * @return: The compute shader.
             */
            ComputeShader buildComputeShader() const;

            private:
            std::unordered_map<ShaderStep, std::string> sources;        // The shader sources.
            std::unordered_map<std::string, GLuint> uniformLocations;   // The uniform block indices.
        };
    }
}