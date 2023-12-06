//
// Created by tomas on 06-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "core/gl/render_shader.h"
#include "core/gl/compute_shader.h"
#include "engine/internal/shader_library.h"


namespace cobalt {
    namespace engine {
        static core::RenderShader parseRenderShader(nlohmann::json& shaderJson, core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            core::Path vertexShaderPath = shadersDirectory + shaderJson["vertex"].get<std::string>();
            core::Path fragmentShaderPath = shadersDirectory + shaderJson["fragment"].get<std::string>();
            std::string vertexShaderSource;
            std::string fragmentShaderSource;
            std::ifstream(vertexShaderPath.getPath()) >> vertexShaderSource;
            std::ifstream(fragmentShaderPath.getPath()) >> fragmentShaderSource;
            builder.addShaderStep(core::ShaderStep::Vertex, vertexShaderSource);
            builder.addShaderStep(core::ShaderStep::Fragment, fragmentShaderSource);
            if (shaderJson.contains("geometry")) {
                core::Path geometryShaderPath = shadersDirectory + shaderJson["geometry"].get<std::string>();
                std::string geometryShaderSource;
                std::ifstream(geometryShaderPath.getPath()) >> geometryShaderSource;
                builder.addShaderStep(core::ShaderStep::Geometry, geometryShaderSource);
            }
            return builder.buildRenderShader();
        }

        static core::ComputeShader parseComputeShader(nlohmann::json& shaderJson, core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            core::Path computeShaderPath = shadersDirectory + shaderJson["compute"].get<std::string>();
            std::string computeShaderSource;
            std::ifstream(computeShaderPath.getPath()) >> computeShaderSource;
            builder.addShaderStep(core::ShaderStep::Compute, computeShaderSource);
            return builder.buildComputeShader();
        }

        ShaderLibrary::ShaderLibrary(core::Path& shadersDirectory)
            : shaders(8) {
            core::Path shadersJsonPath = shadersDirectory;
            shadersJsonPath += "shaders.json";
            if (!shadersJsonPath.exists()) {
                return;
            }
            std::ifstream shadersJsonFile(shadersJsonPath.getPath());
            nlohmann::json shadersJson;
            shadersJsonFile >> shadersJson;
            for (auto& shaderJson : shadersJson) {
                core::Path shaderPath = shadersDirectory;
                if (shaderJson["type"].get<std::string>() == "render") {
                    shaders.push({shaderJson.get<std::string>(), parseRenderShader(shaderJson, shadersDirectory)});
                }
                else if (shaderJson["type"].get<std::string>() == "compute") {
                    shaders.push({shaderJson.get<std::string>(), parseComputeShader(shaderJson, shadersDirectory)});
                }
            }
        }

        ShaderID ShaderLibrary::getShaderID(const std::string& name) {
            for (core::uint64 i = 0; i < shaders.getSize(); i++) {
                if (shaders[i].name == name) {
                    return i + 1;
                }
            }
            return 0;
        }

        core::Shader& ShaderLibrary::getShader(ShaderID id) {
            return shaders[id - 1].shader;
        }
    }
}