// Created by tomas on
// 24-12-2023

#include "core/ecs/exception.h"
#include "engine/material/plugin.h"

namespace cobalt {
    namespace engine {
        MaterialID::MaterialID(const uint handle, const std::string& name, MaterialLibrary& owner) noexcept
            : handle(handle), name(name), owner(owner) {}

        MaterialID::MaterialID(const MaterialID& other) noexcept : handle(other.handle), name(other.name), owner(other.owner) {}

        MaterialID::MaterialID(MaterialID&& other) noexcept : handle(other.handle), name(std::move(other.name)), owner(other.owner) {}

        MaterialID& MaterialID::operator=(const MaterialID& other) noexcept {
            handle = other.handle;
            name = other.name;
            return *this;
        }

        MaterialID& MaterialID::operator=(MaterialID&& other) noexcept {
            handle = Move(other.handle);
            name = Move(other.name);
            return *this;
        }

        bool MaterialID::operator==(const MaterialID& other) const { return handle == other.handle; }

        bool MaterialID::operator!=(const MaterialID& other) const { return handle != other.handle; }

        const uint MaterialID::getHandle() const { return handle; }

        const std::string& MaterialID::getName() const { return name; }

        Material& MaterialID::getMaterial() { return owner.getMaterial(*this); }

        MaterialLibrary::MaterialLibrary(TextureLibrary& textureLibrary, ShaderLibrary& shaderLibrary) noexcept
            : textureLibrary(textureLibrary), shaderLibrary(shaderLibrary) {}

        MaterialID& MaterialLibrary::getMaterialID(const std::string& name) {
            try {
                return materialNames.at(name);
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, MaterialLibrary>("Material with name " + name + " not found");
            }
        }

        Material& MaterialLibrary::getMaterial(const MaterialID& id) {
            try {
                return materials.at(materialNames.at(id.name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, MaterialLibrary>("Material with handle " + std::to_string(id.getHandle()) +
                                                                                  " not found");
            }
        }

        Material& MaterialLibrary::getMaterial(const std::string& name) {
            try {
                return materials.at(materialNames.at(name));
            } catch (const std::out_of_range& e) {
                throw core::ecs::PluginException<MaterialPlugin, MaterialLibrary>("Material with name " + name + " not found");
            }
        }

        MaterialID& MaterialLibrary::makePBR(const std::string& name, const TextureID& albedo, const TextureID& normal, const TextureID& mrao) {
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(
                id, MaterialFactory::createMaterialPBR(shaderLibrary.getShader("pbr"), textureLibrary.getTexture(albedo).as<core::gl::Texture2D>(),
                                                       textureLibrary.getTexture(normal).as<core::gl::Texture2D>(),
                                                       textureLibrary.getTexture(mrao).as<core::gl::Texture2D>()));
            return materialNames.at(name);
        }

        MaterialID& MaterialLibrary::makePBR(const std::string& name, const core::Color albedo, const float metallic, const float roughness,
                                             const float ao) {
            TextureID normalID =
                textureLibrary.makeTexture("CB_default-normal", (void*)core::gl::Texture2D::DEFAULT_NORMAL, core::gl::TextureEncodings::RGBA::Bits8);
            uchar albedoData[4];
            albedo.toUChar(albedoData);
            TextureID albedoID = textureLibrary.makeTexture(albedo.toString(), (void*)&albedoData, core::gl::TextureEncodings::RGBA::Bits8);
            core::Color mrao(metallic, roughness, ao);
            uchar mraoData[4];
            mrao.toUChar(mraoData);
            TextureID mraoID = textureLibrary.makeTexture(mrao.toString(), (void*)&mraoData, core::gl::TextureEncodings::RGB::Bits8);
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(
                id, MaterialFactory::createMaterialPBR(shaderLibrary.getShader("pbr"), textureLibrary.getTexture(albedoID).as<core::gl::Texture2D>(),
                                                       textureLibrary.getTexture(normalID).as<core::gl::Texture2D>(),
                                                       textureLibrary.getTexture(mraoID).as<core::gl::Texture2D>()));
            return materialNames.at(name);
        }

        MaterialID& MaterialLibrary::makeUnlit(const std::string& name, const TextureID& color) {
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(id, MaterialFactory::createMaterialUnlit(shaderLibrary.getShader("unlit"),
                                                                       textureLibrary.getTexture(color).as<core::gl::Texture2D>()));
            return materialNames.at(name);
        }

        MaterialID& MaterialLibrary::makeUnlit(const std::string& name, const core::Color color) {
            TextureID colorID = textureLibrary.makeTexture(color.toString(), (void*)&color, core::gl::TextureEncodings::RGBA::Bits8);
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(id, MaterialFactory::createMaterialUnlit(shaderLibrary.getShader("unlit"),
                                                                       textureLibrary.getTexture(colorID).as<core::gl::Texture2D>()));
            return materialNames.at(name);
        }

        MaterialID& MaterialLibrary::makeFromShader(const std::string& name, const ShaderID& shader,
                                                    const UMap<std::string, const core::gl::Texture2D&>& textures) {
            UMap<std::string, const core::gl::Texture&> textureMap;
            for (auto& texture : textures) {
                textureMap.emplace(texture.first, texture.second);
            }
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(id, MaterialFactory::createMaterial(shaderLibrary.getShader(shader), textureMap));
            return materialNames.at(name);
        }

        MaterialID& MaterialLibrary::makeFromShader(const std::string& name, const std::string& shader,
                                                    const UMap<std::string, const core::gl::Texture2D&>& textures) {
            UMap<std::string, const core::gl::Texture&> textureMap;
            for (auto& texture : textures) {
                textureMap.emplace(texture.first, texture.second);
            }
            MaterialID id(materials.size(), name, *this);
            materialNames.emplace(name, id);
            materials.erase(id);
            materials.emplace(id, MaterialFactory::createMaterial(shaderLibrary.getShader(shader), textureMap));
            return materialNames.at(name);
        }
    }  // namespace engine
}  // namespace cobalt