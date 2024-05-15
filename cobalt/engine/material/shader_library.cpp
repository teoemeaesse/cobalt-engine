// Created by tomas on
// 06-12-2023

#include "engine/material/shader_library.h"

namespace cobalt {
    namespace engine {
        Scope<ShaderLibrary> ShaderLibrary::instance;

        static core::gl::Shader parseRenderShader(nlohmann::json& shaderJson, const core::io::Path& shadersDirectory, const std::string& shaderName) {
            CB_INFO("Loading render shader: {}", shaderName);
            core::gl::ShaderBuilder builder;
            std::string vertexName = shaderJson["vertex"].get<std::string>();
            std::string fragmentName = shaderJson["fragment"].get<std::string>();
            core::io::File vertexFile(shadersDirectory + vertexName);
            core::io::File fragmentFile(shadersDirectory + fragmentName);
            CB_INFO("From vertex source: {}", vertexName);
            CB_INFO("From fragment source: {}", fragmentName);
            builder.addShaderStep(core::gl::ShaderStep::Vertex, vertexFile.read());
            builder.addShaderStep(core::gl::ShaderStep::Fragment, fragmentFile.read());
            if (shaderJson.contains("geometry")) {
                std::string geometryName = shaderJson["geometry"].get<std::string>();
                core::io::File geometryFile(shadersDirectory + geometryName);
                CB_INFO("From geometry source: {}", geometryName);
                builder.addShaderStep(core::gl::ShaderStep::Geometry, geometryFile.read());
            }
            return builder.buildRenderShader();
        }

        static core::gl::Shader parseComputeShader(nlohmann::json& shaderJson, const core::io::Path& shadersDirectory,
                                                   const std::string& shaderName) {
            CB_INFO("Loading compute shader: {}", shaderName);
            core::gl::ShaderBuilder builder;
            std::string computeName = shaderJson["compute"].get<std::string>();
            core::io::File computeFile(shadersDirectory + computeName);
            CB_INFO("From source: {}", computeName);
            builder.addShaderStep(core::gl::ShaderStep::Compute, computeFile.read());
            return builder.buildComputeShader();
        }

        void ShaderLibrary::loadShaders(const core::io::Path& shadersDirectory) {
            core::io::Path shadersJsonPath = shadersDirectory;
            shadersJsonPath += "shaders.json";
            if (!shadersJsonPath.exists()) {
                CB_WARN("No shaders.json file found in shaders directory: {}", shadersDirectory.getPath());
                return;
            }
            std::ifstream shadersJsonFile(shadersJsonPath.getPath());
            nlohmann::json shadersJson = nlohmann::json::parse(shadersJsonFile);
            CB_INFO("Loading shaders from: {}", shadersDirectory.getPath());
            CB_INFO("Found {} shaders", shadersJson.size());
            for (auto it = shadersJson.begin(); it != shadersJson.end(); ++it) {
                std::string shaderName = it.key();
                nlohmann::json shaderJson = it.value();
                if (shaderJson["type"].get<std::string>() == "render") {
                    shaders.emplace_back(shaderName, Move(parseRenderShader(shaderJson, shadersDirectory, shaderName)));
                } else if (shaderJson["type"].get<std::string>() == "compute") {
                    shaders.emplace_back(shaderName, Move(parseComputeShader(shaderJson, shadersDirectory, shaderName)));
                }
            }
        }

        const ShaderID ShaderLibrary::getShaderID(const std::string& name) {
            for (uint64 i = 0; i < shaders.size(); i++) {
                if (shaders[i].name == name) {
                    return i + 1;
                }
            }
            CB_WARN("Shader ID {0} not found, returning default shader", name);
            return 0;
        }

        core::gl::Shader& ShaderLibrary::getShader(const ShaderID id) { return shaders[id - 1].shader; }

        core::gl::Shader& ShaderLibrary::getShader(const std::string& name) { return getShader(getShaderID(name)); }

        void ShaderLibrary::init() { instance = CreateScope<ShaderLibrary>(); }

        ShaderLibrary& ShaderLibrary::getShaderLibrary() { return *instance; }
    }  // namespace engine
}  // namespace cobalt