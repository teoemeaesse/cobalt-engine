//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/gl/shader.h"
#include "core/pch.h"


namespace cobalt {
    namespace engine {
        using ShaderID = core::uint64;

        class ShaderLibrary {
            public:
            struct ShaderEntry {
                std::string name;                       // The name of the shader.
                std::unique_ptr<core::Shader> shader;   // The shader.
            };

            /* Creates an empty shader library.
             * @return: The shader library.
             */
            ShaderLibrary();
            /* Destroys the shader library and all shaders it contains.
             */
            ~ShaderLibrary() = default;

            /* Loads all shaders from the given directory.
             * This directory should contain a file called "shaders.json" which
             * contains a list of internal shader names and their corresponding
             * vertex/fragment/geometry or compute shader source files.
             * @param shadersDirectory: The directory containing the shader files.
             */
            void loadShaders(const core::Path& shadersDirectory);

            /* Returns the shader ID of the shader with the given name.
             * If the shader does not exist, returns 0.
             * @param name: The name of the shader.
             */
            const ShaderID getShaderID(const std::string& name);

            /* Returns the shader with the given ID.
             * If the shader does not exist, returns a null shader.
             * @param id: The ID of the shader.
             */
            core::Shader& getShader(const ShaderID id);

            /* Initializes the singleton instance of the shader library.
             */
            static void init();
            /* Returns the singleton instance of the shader library.
             * @return: The shader library.
             */
            static ShaderLibrary& getShaderLibrary();

            private:
            core::Vector<ShaderEntry> shaders;  // The shaders in the library.

            static std::unique_ptr<ShaderLibrary> instance; // The singleton instance of the shader library.
        };
    }
}

#define CB_SHADER_LIBRARY ::cobalt::engine::ShaderLibrary::getShaderLibrary()