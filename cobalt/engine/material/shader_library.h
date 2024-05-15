// Created by tomas on
// 06-12-2023

#pragma once

#include "core/gl/shader.h"

namespace cobalt {
    namespace engine {
        using ShaderID = uint;

        class ShaderLibrary {
            public:
            struct ShaderEntry {
                std::string name;         // The name of the shader.
                core::gl::Shader shader;  // The shader.

                /**
                 * @brief Creates a new shader entry.
                 * @param name The name of the shader.
                 * @param shader The shader.
                 * @return The shader entry.
                 */
                ShaderEntry(const std::string& name, core::gl::Shader&& shader) : name(name), shader(Move(shader)) {}
            };

            /**
             * @brief Creates an empty shader library.
             * @return The shader library.
             */
            ShaderLibrary() = default;
            /**
             * @brief Destroys the shader library and all shaders it contains.
             */
            ~ShaderLibrary() = default;

            /**
             * @brief Loads all shaders from the given directory. This directory should contain a file called "shaders.json" which contains a list of
             * internal shader names and their corresponding vertex/fragment/geometry or compute shader source files.
             * @param shadersDirectory The directory containing the shader files.
             */
            void loadShaders(const core::io::Path& shadersDirectory);

            /**
             * @brief Returns the shader ID of the shader with the given name. If the shader does not exist, returns 0.
             * @param name The name of the shader.
             * @return The shader ID.
             */
            const ShaderID getShaderID(const std::string& name);

            /**
             * @brief Returns the shader with the given ID. If the shader does not exist, returns a null shader.
             * @param id The ID of the shader.
             * @return The shader.
             */
            core::gl::Shader& getShader(const ShaderID id);
            /**
             * @brief Returns the shader with the given name. If the shader does not exist, returns a null shader.
             * @param name The name of the shader.
             * @return The shader.
             */
            core::gl::Shader& getShader(const std::string& name);

            /**
             * @brief Initializes the singleton instance of the shader library.
             */
            static void init();
            /**
             * @brief Returns the singleton instance of the shader library.
             * @return The shader library.
             */
            static ShaderLibrary& getShaderLibrary();

            private:
            Deque<ShaderEntry> shaders;  // The shaders in the library.

            static Scope<ShaderLibrary> instance;  // The singleton instance of the shader library.
        };
    }  // namespace engine
}  // namespace cobalt

#define CB_SHADER_LIBRARY ::cobalt::engine::ShaderLibrary::getShaderLibrary()