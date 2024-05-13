// Created by tomas on
// 24-12-2023

#pragma once

#include "engine/internal/shader_library.h"
#include "engine/internal/texture_library.h"
#include "engine/material_pbr/material.h"

namespace cobalt {
    namespace engine {
        class MaterialID {
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
             */
            MaterialID(const MaterialID& other) noexcept;
            /**
             * @brief Default move constructor.
             */
            MaterialID(MaterialID&& other) noexcept;
            /**
             * @brief Default copy assignment operator.
             */
            MaterialID& operator=(const MaterialID& other) noexcept;
            /**
             * @brief Default move assignment operator.
             */
            MaterialID& operator=(MaterialID&& other) noexcept;

            /**
             * @brief Check if two material IDs are equal.
             * @param other The other material ID.
             * @return True if the handles are equal, false otherwise.
             */
            bool operator==(const MaterialID& other) const;

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
            MaterialPBR& getMaterial();

            private:
            uint handle;
            std::string name;
            MaterialLibrary& owner;
        };

        class MaterialLibrary {
            public:
            struct MaterialEntry {
                std::string name;
                MaterialPBR material;

                /**
                 * @brief Creates a new material entry.
                 * @param name The name of the material.
                 * @param material The material.
                 * @return The material entry.
                 */
                MaterialEntry(const std::string& name, const MaterialPBR& material) : name(name), material(material) {}
            };

            /**
             * @brief Default constructor.
             */
            MaterialLibrary() = default;
            /**
             * @brief Default destructor.
             */
            ~MaterialLibrary() = default;

            /**
             * @brief Returns the material ID of the material with the given name.
             * If the material does not exist, returns 0.
             * @param name The name of the material.
             */
            const MaterialID getMaterialID(const std::string& name);

            /**
             * @brief Returns the material with the given ID.
             * If the material does not exist, returns a null material.
             * @param id The ID of the material.
             * @return The material.
             */
            MaterialPBR& getMaterial(const MaterialID id);

            /**
             * @brief Creates a new PBR material.
             * @param name The name of the material.
             * @param shader The shader program.
             * @param albedoMap The surface albedo map.
             * @param normalMap The surface normal map.
             * @param mraoMap The metallic (R), roughness (G) and AO (B) map.
             * @return The material.
             */
            const MaterialID makePBR(const std::string& name, const TextureID& albedo, const TextureID& normal, const TextureID& mrao);
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
            const MaterialID makePBR(const std::string& name, const core::Color albedo, const float metallic, const float roughness, const float ao);

            /**
             * @brief Creates a new unlit material.
             * @param name The name of the material.
             * @param color The color of the material.
             * @return The material. TODO: Variadic template for different material
             * types.
             */
            const MaterialID makeUnlit(const std::string& name, const TextureID& color);
            /**
             * @brief Creates a new unlit material.
             * @param name The name of the material.
             * @param color The color of the material.
             * @return The material. TODO: Variadic template for different material
             * types.
             */
            const MaterialID makeUnlit(const std::string& name, const core::Color color);

            /**
             * @brief Creates a new material from the given shader.
             * @param name The name of the material.
             * @param shader The shader program.
             * @param textures The uniform textures of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            const MaterialID makeFromShader(
                const std::string& name, const ShaderID& shader,
                const UMap<std::string, const core::gl::Texture2D&>& textures = UMap<std::string, const core::gl::Texture2D&>());
            /**
             * @brief Creates a new material from the given shader.
             * @param name The name of the material.
             * @param shader The name of shader program.
             * @param textures The uniform textures of the material.
             * @return The material. TODO: Variadic template for different material types.
             */
            const MaterialID makeFromShader(
                const std::string& name, const std::string& shader,
                const UMap<std::string, const core::gl::Texture2D&>& textures = UMap<std::string, const core::gl::Texture2D&>());

            private:
            Deque<MaterialEntry> materials;  // The materials in the library.
        };
    }  // namespace engine
}  // namespace cobalt