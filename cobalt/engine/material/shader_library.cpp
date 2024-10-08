// Created by tomas on
// 06-12-2023

#include "engine/material/shader_library.h"

#include "core/ecs/exception.h"
#include "engine/material/plugin.h"

namespace cobalt {
    namespace engine {
        ShaderID::ShaderID(const uint handle, const std::string& name, ShaderLibrary& owner) noexcept : handle(handle), name(name), owner(owner) {}

        bool ShaderID::operator==(const ShaderID& other) const noexcept { return handle == other.handle; }

        bool ShaderID::operator!=(const ShaderID& other) const noexcept { return handle != other.handle; }

        const uint ShaderID::getHandle() const noexcept { return handle; }

        const std::string& ShaderID::getName() const noexcept { return name; }

        core::gl::Shader& ShaderID::getShader() noexcept { return owner.getShader(*this); }

        ShaderID::operator std::string() const noexcept { return std::to_string(handle) + ": " + name; }

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
                ShaderID id(shaders.size(), shaderName, *this);
                shaderNames.emplace(shaderName, id);
                shaders.erase(id);
                if (shaderJson["type"].get<std::string>() == "render") {
                    shaders.emplace(id, parseRenderShader(shaderJson, shadersDirectory, shaderName));
                } else if (shaderJson["type"].get<std::string>() == "compute") {
                    shaders.emplace(id, Move(parseComputeShader(shaderJson, shadersDirectory, shaderName)));
                } else {
                    throw core::ecs::PluginException<MaterialPlugin, ShaderLibrary>("Unknown shader type: " + shaderJson["type"].get<std::string>());
                }
            }
        }

        ShaderID& ShaderLibrary::getShaderID(const std::string& name) {
            try {
                return shaderNames.at(name);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, ShaderLibrary>("Shader with name \"" + name + "\" not found");
            }
        }

        core::gl::Shader& ShaderLibrary::getShader(ShaderID& id) {
            try {
                return shaders.at(id);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, ShaderLibrary>("Shader ID " + std::string(id) + " not found");
            }
        }

        core::gl::Shader& ShaderLibrary::getShader(const std::string& name) {
            try {
                return getShader(shaderNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, ShaderLibrary>("Shader with name \"" + name + "\" not found");
            }
        }
    }  // namespace engine
}  // namespace cobalt