//
// Created by tomas on 06-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "engine/internal/shader_library.h"
#include "core/gl/render_shader.h"
#include "core/gl/compute_shader.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace engine {
        static core::RenderShader parseRenderShader(nlohmann::json& shaderJson, const core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            core::Path vertexShaderPath = shadersDirectory + shaderJson["vertex"].get<std::string>();
            core::Path fragmentShaderPath = shadersDirectory + shaderJson["fragment"].get<std::string>();
            CB_INFO("From vertex source: {}", vertexShaderPath.getFileName());
            std::ifstream vertexFile(vertexShaderPath.getPath());
            std::stringstream vertexStream;
            vertexStream << vertexFile.rdbuf();
            CB_INFO("From fragment source: {}", fragmentShaderPath.getFileName());
            std::ifstream fragmentFile(fragmentShaderPath.getPath());
            std::stringstream fragmentStream;
            fragmentStream << fragmentFile.rdbuf();
            builder.addShaderStep(core::ShaderStep::Vertex, vertexStream.str());
            builder.addShaderStep(core::ShaderStep::Fragment, fragmentStream.str());
            if (shaderJson.contains("geometry")) {
                core::Path geometryShaderPath = shadersDirectory + shaderJson["geometry"].get<std::string>();
                CB_INFO("From geometry source: {}", geometryShaderPath.getFileName());
                std::ifstream geometryFile(geometryShaderPath.getPath());
                std::stringstream geometryStream;
                geometryStream << geometryFile.rdbuf();
                builder.addShaderStep(core::ShaderStep::Geometry, geometryStream.str());
            }
            return builder.buildRenderShader();
        }

        static core::ComputeShader parseComputeShader(nlohmann::json& shaderJson, const core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            core::Path computeShaderPath = shadersDirectory + shaderJson["compute"].get<std::string>();
            CB_INFO("From source: {}", computeShaderPath.getFileName());
            std::ifstream computeFile(computeShaderPath.getPath());
            std::stringstream computeStream;
            computeStream << computeFile.rdbuf();
            builder.addShaderStep(core::ShaderStep::Compute, computeStream.str());
            return builder.buildComputeShader();
        }

        ShaderLibrary::ShaderLibrary()
            : shaders(8) {}

        void ShaderLibrary::loadShaders(const core::Path& shadersDirectory) {
            core::Path shadersJsonPath = shadersDirectory;
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
                    CB_INFO("Loading render shader: {}", shaderName);
                    shaders.push({shaderName, parseRenderShader(shaderJson, shadersDirectory)});
                }
                else if (shaderJson["type"].get<std::string>() == "compute") {
                    CB_INFO("Loading compute shader: {}", shaderName);
                    shaders.push({shaderName, parseComputeShader(shaderJson, shadersDirectory)});
                }
            }
        }

        const ShaderID ShaderLibrary::getShaderID(const std::string& name) {
            for (core::uint64 i = 0; i < shaders.getSize(); i++) {
                if (shaders[i].name == name) {
                    return i + 1;
                }
            }
            return 0;
        }

        const core::Shader& ShaderLibrary::getShader(const ShaderID id) {
            return shaders[id - 1].shader;
        }
    }
}