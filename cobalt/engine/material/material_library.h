// Created by tomas on
// 24-12-2023

#pragma once

#include "engine/material/material.h"
#include "engine/material/shader_library.h"
#include "engine/material/texture_library.h"

namespace cobalt {
    namespace engine {
        class MaterialLibrary;

        class MaterialID : public core::ecs::Component {
            friend class MaterialLibrary;

            public:
            /**
             * @brief Create a material ID with the given handle and name.
             * @param handle The handle of the material.
             * @param name The name of the material.
             * @param owner The material library that owns the material.
             */
            MaterialID(const uint handle, const std::string& name, MaterialLibrary& owner) noexcept;
            /**
             * @brief Default destructor.
             */
            ~MaterialID() noexcept = default;
            /**
             * @brief Default copy constructor.
             * @param other The other material ID.
             */
            MaterialID(const MaterialID& other) noexcept;
            /**
             * @brief Default move constructor.
             * @param other The other material ID.
             */
            MaterialID(MaterialID&& other) noexcept;
            /**
             * @brief Default copy assignment operator.
             * @param other The other material ID.
             * @return The copied material ID.
             */
            MaterialID& operator=(const MaterialID& other) noexcept;
            /**
             * @brief Default move assignment operator.
             * @param other The other material ID.
             * @return The moved material ID.
             */
            MaterialID& operator=(MaterialID&& other) noexcept;

            /**
             * @brief Checks if two material IDs are equal.
             * @param other The other material ID.
             * @return True if the handles are equal, false otherwise.
             */
            bool operator==(const MaterialID& other) const;
            /**
             * @brief Checks if two material IDs are not equal.
             * @param other The other material ID.
             * @return True if the handles are not equal, false otherwise.
             */
            bool operator!=(const MaterialID& other) const;

            /**
             * @brief Get the handle of the material.
             * @return The handle of the material.
             */
            const uint getHandle() const;
            /**
             * @brief Get the name of the material.
             * @return The name of the material.
             */
            const std::string& getName() const;
            /**
             * @brief Get the material.
             * @return The material.
             */
            Material& getMaterial();

            private:
            uint handle;
            std::string name;
            MaterialLibrary& owner;
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::engine::MaterialID> {
        size_t operator()(const cobalt::engine::MaterialID& id) const { return hash<uint>()(id.getHandle()); }
    };
}  // namespace std

namespace cobalt {
    namespace engine {
        class MaterialLibrary : public core::ecs::Resource {
            public:
            /**
             * @brief Default constructor.
             * @param textureLibrary The texture library to store the materials' textures.
             */
            explicit MaterialLibrary(TextureLibrary& textureLibrary) noexcept;
            /**
             * @brief Default destructor.
             */
            ~MaterialLibrary() noexcept = default;

            /**
             * @brief Returns the material ID of the material with the given name.
             * @param name The name of the material.
             * @return The material ID.
             * @throws core::ecs::PluginException<MaterialPlugin, MaterialLibrary> If the material does not exist.
             */
            MaterialID& getMaterialID(const std::string& name);

            /**
             * @brief Returns the material with the given ID.
             * @param id The ID of the material.
             * @return The material.
             * @throws core::ecs::PluginException<MaterialPlugin, MaterialLibrary> If the material does not exist.
             */
            Material& getMaterial(const MaterialID& id);

            /**
             * @brief Returns the material with the given name.
             * @param name The name of the material.
             * @return The material.
             * @throws core::ecs::PluginException<MaterialPlugin, MaterialLibrary> If the material does not exist.
             */
            Material& getMaterial(const std::string& name);

            /**
             * @brief Creates a new PBR material.
             * @param name The name of the material.
             * @param shader The shader program.
             * @param albedoMap The surface albedo map.
             * @param normalMap The surface normal map.
             * @param mraoMap The metallic (R), roughness (G) and AO (B) map.
             * @return The material.
             */
            MaterialID& makePBR(const std::string& name, const TextureID& albedo, const TextureID& normal, const TextureID& mrao);
            /**
             * @brief Creates a new PBR material.
             * @param name The name of the material.
             * @param shader The shader program.
             * @param albedo The surface albedo.
             * @param metallic The surface metallic value (0.0f - 1.0f).
             * @param roughness The surface roughness value (0.0f - 1.0f).
             * @param ao The surface ambient occlusion value (0.0f - 1.0f).
             * @return The material.
             */
            MaterialID& makePBR(const std::string& name, const core::Color albedo, const float metallic, const float roughness, const float ao);

            /**
             * @brief Creates a new unlit material.
             * @param name The name of the material.
             * @param color The color of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            MaterialID& makeUnlit(const std::string& name, const TextureID& color);
            /**
             * @brief Creates a new unlit material.
             * @param name The name of the material.
             * @param color The color of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            MaterialID& makeUnlit(const std::string& name, const core::Color color);

            /**
             * @brief Creates a new material from the given shader.
             * @param name The name of the material.
             * @param shader The shader program.
             * @param textures The uniform textures of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            MaterialID& makeFromShader(
                const std::string& name, const ShaderID& shader,
                const UMap<std::string, const core::gl::Texture2D&>& textures = UMap<std::string, const core::gl::Texture2D&>());
            /**
             * @brief Creates a new material from the given shader.
             * @param name The name of the material.
             * @param shader The name of shader program.
             * @param textures The uniform textures of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            MaterialID& makeFromShader(
                const std::string& name, const std::string& shader,
                const UMap<std::string, const core::gl::Texture2D&>& textures = UMap<std::string, const core::gl::Texture2D&>());

            private:
            UMap<MaterialID, Material> materials;         // The materials in the library.
            UMap<std::string, MaterialID> materialNames;  // The names of the materials.
            TextureLibrary& textureLibrary;               // The texture library.
        };
    }  // namespace engine
}  // namespace cobalt