//
// Created by tomas on 06-12-2023.
//

#pragma once

#include "core/io/path.h"
#include "core/utils/types.h"
#include "core/gl/shader.h"


namespace cobalt {
    namespace engine {
        using ShaderID = core::int64;

        class ShaderLibrary {
            public:
            /* Creates a shader library from a directory containing shader files.
             * This directory should contain a file called "shaders.json" which
             * contains a list of internal shader names and their corresponding
             * vertex/fragment/geometry or compute shader source files.
             * @param shadersDirectory: The directory containing the shader files.
             */
            ShaderLibrary(core::Path& shadersDirectory);
            /* Destroys the shader library and all shaders it contains.
             */
            ~ShaderLibrary();

            /* Returns the shader ID of the shader with the given name.
             * If the shader does not exist, returns 0.
             * @param name: The name of the shader.
             */
            ShaderID getShaderID(const std::string& name);

            /* Returns the shader with the given ID.
             * If the shader does not exist, returns a null shader.
             * @param id: The ID of the shader.
             */
            core::Shader& getShader(ShaderID id);
        };
    }
}