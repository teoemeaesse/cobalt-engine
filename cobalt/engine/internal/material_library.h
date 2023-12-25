//
// Created by tomas on 24-12-2023.
//

#pragma once

#include "core/pch.h"
#include "core/gfx/material.h"
#include "engine/internal/texture_library.h"


namespace cobalt {
    namespace engine {
        using MaterialID = core::uint;

        class MaterialLibrary {
            public:
            struct MaterialEntry {
                std::string name;
                core::Material material;

                /** Creates a new material entry.
                 * @param name: The name of the material.
                 * @param material: The material.
                 * @return: The material entry.
                 */
                MaterialEntry(const std::string& name, const core::Material& material) :
                    name(name),
                    material(material)
                {}
            };

            /** Creates an empty material library.
             * @return: The material library.
             */
            MaterialLibrary();
            /** Destroys the material library and all materials it contains.
             */
            ~MaterialLibrary() = default;

            /** Returns the material ID of the material with the given name.
             * If the material does not exist, returns 0.
             * @param name: The name of the material.
             */
            const MaterialID getMaterialID(const std::string& name);

            /** Returns the material with the given ID.
             * If the material does not exist, returns a null material.
             * @param id: The ID of the material.
             * @return: The material.
             */
            core::Material& getMaterial(const MaterialID id);

            /** Creates a new PBR material.
             * @param name: The name of the material.
             * @param shader: The shader program.
             * @param albedoMap: The surface albedo map.
             * @param normalMap: The surface normal map.
             * @param mraoMap: The metallic (R), roughness (G) and AO (B) map.
             * @return: The material.
             */
            const MaterialID makePBR(
                const std::string& name,
                const TextureID& albedo,
                const TextureID& normal,
                const TextureID& mrao);
            
            /** Creates a new PBR material.
             * @param name: The name of the material.
             * @param shader: The shader program.
             * @param albedo: The surface albedo.
             * @param metallic: The surface metallic value (0.0f - 1.0f).
             * @param roughness: The surface roughness value (0.0f - 1.0f).
             * @param ao: The surface ambient occlusion value (0.0f - 1.0f).
             * @return: The material.
             */
            const MaterialID makePBR(
                const std::string& name,
                const core::Color albedo,
                const float metallic,
                const float roughness,
                const float ao);

            /** Initializes the singleton instance of the material library.
             * This loads the default materials, so it needs to be called after
             * the texture and shader libraries have been initialized!
             */
            static void init();
            /** Returns the singleton instance of the material library.
             * @return: The material library.
             */
            static MaterialLibrary& getMaterialLibrary();

            private:
            core::Deque<MaterialEntry> materials;   // The materials in the library.

            static core::Scope<MaterialLibrary> instance;   // The singleton instance of the material library.
        };
    }
}

#define CB_MATERIAL_LIBRARY ::cobalt::engine::MaterialLibrary::getMaterialLibrary()