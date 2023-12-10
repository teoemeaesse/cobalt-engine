//
// Created by tomas on 06-12-2023.
//

#include <fstream>

#include "json/json.hpp"

#include "engine/internal/shader_library.h"
#include "core/io/file.h"
#include "core/gl/render_shader.h"
#include "core/gl/compute_shader.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace engine {
        static std::unique_ptr<core::RenderShader> parseRenderShader(nlohmann::json& shaderJson, const core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            std::string vertexName = shaderJson["vertex"].get<std::string>();
            std::string fragmentName = shaderJson["fragment"].get<std::string>();
            core::File vertexFile(shadersDirectory + vertexName);
            core::File fragmentFile(shadersDirectory + fragmentName);
            CB_INFO("From vertex source: {}", vertexName);
            CB_INFO("From fragment source: {}", fragmentName);
            builder.addShaderStep(core::ShaderStep::Vertex, vertexFile.read());
            builder.addShaderStep(core::ShaderStep::Fragment, fragmentFile.read());
            if (shaderJson.contains("geometry")) {
                std::string geometryName = shaderJson["geometry"].get<std::string>();
                core::File geometryFile(shadersDirectory + geometryName);
                CB_INFO("From geometry source: {}", geometryName);
                builder.addShaderStep(core::ShaderStep::Geometry, geometryFile.read());
            }
            return builder.buildRenderShader();
        }

        static std::unique_ptr<core::ComputeShader> parseComputeShader(nlohmann::json& shaderJson, const core::Path& shadersDirectory) {
            core::ShaderBuilder builder;
            std::string computeName = shaderJson["compute"].get<std::string>();
            core::File computeFile(shadersDirectory + computeName);
            CB_INFO("From source: {}", computeName);
            builder.addShaderStep(core::ShaderStep::Compute, computeFile.read());
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
                    shaders.push({shaderName, std::move(parseRenderShader(shaderJson, shadersDirectory))});
                }
                else if (shaderJson["type"].get<std::string>() == "compute") {
                    CB_INFO("Loading compute shader: {}", shaderName);
                    shaders.push({shaderName, std::move(parseComputeShader(shaderJson, shadersDirectory))});
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

        core::Shader& ShaderLibrary::getShader(const ShaderID id) {
            return *shaders[id - 1].shader;
        }
    }
}