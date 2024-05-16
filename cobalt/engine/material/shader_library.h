// Created by tomas on
// 06-12-2023

#pragma once

#include "core/ecs/resource/resource.h"
#include "core/gl/shader.h"

namespace cobalt {
    namespace engine {
        class ShaderLibrary;

        class ShaderID {
            friend class ShaderLibrary;

            public:
            /**
             * @brief Creates a new shader ID.
             * @param handle The handle of the shader.
             * @param name The name of the shader.
             * @param owner The shader library that owns the shader.
             */
            ShaderID(const uint handle, const std::string& name, ShaderLibrary& owner) noexcept;
            /**
             * @brief Default destructor.
             */
            ~ShaderID() noexcept = default;
            /**
             * @brief Default copy constructor.
             * @param other The other shader ID.
             */
            ShaderID(const ShaderID& other) noexcept = default;
            /**
             * @brief Default move constructor.
             * @param other The other shader ID.
             */
            ShaderID(ShaderID&& other) noexcept = default;
            /**
             * @brief Default copy assignment operator.
             * @param other The other shader ID.
             * @return The new shader ID.
             */
            ShaderID& operator=(const ShaderID& other) noexcept = delete;
            /**
             * @brief Default move assignment operator.
             * @param other The other shader ID.
             * @return The new shader ID.
             */
            ShaderID& operator=(ShaderID&& other) noexcept = delete;

            /**
             * @brief Checks if two shader IDs are equal.
             * @param other The other shader ID.
             * @return True if the handles are equal, false otherwise.
             */
            bool operator==(const ShaderID& other) const noexcept;
            /**
             * @brief Checks if two shader IDs are not equal.
             * @param other The other shader ID.
             * @return True if the handles are not equal, false otherwise.
             */
            bool operator!=(const ShaderID& other) const noexcept;

            /**
             * @brief Returns the handle of the shader.
             * @return The handle.
             */
            const uint getHandle() const noexcept;
            /**
             * @brief Returns the name of the shader.
             * @return The name.
             */
            const std::string& getName() const noexcept;
            /**
             * @brief Returns the shader.
             * @return The shader.
             */
            core::gl::Shader& getShader() noexcept;

            /**
             * @brief Converts the shader ID to a human-readable string.
             * @return The string representation.
             */
            operator std::string() const noexcept;

            private:
            uint handle;
            std::string name;
            ShaderLibrary& owner;
        };
    }  // namespace engine
}  // namespace cobalt

namespace std {
    template <>
    struct hash<cobalt::engine::ShaderID> {
        size_t operator()(const cobalt::engine::ShaderID& id) const { return hash<uint>()(id.getHandle()); }
    };
}  // namespace std

namespace cobalt {
    namespace engine {
        class ShaderLibrary : public core::ecs::Resource {
            public:
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
             * @throws core::ecs::PluginException<MaterialPlugin, ShaderLibrary> If the shaders.json file does not exist.
             */
            void loadShaders(const core::io::Path& shadersDirectory);

            /**
             * @brief Returns the shader ID of the shader with the given name. If the shader does not exist, returns 0.
             * @param name The name of the shader.
             * @return The shader ID.
             * @throws core::ecs::PluginException<MaterialPlugin, ShaderLibrary> If the shader does not exist.
             */
            ShaderID& getShaderID(const std::string& name);

            /**
             * @brief Returns the shader with the given ID. If the shader does not exist, returns a null shader.
             * @param id The ID of the shader.
             * @return The shader.
             * @throws core::ecs::PluginException<MaterialPlugin, ShaderLibrary> If the shader does not exist.
             */
            core::gl::Shader& getShader(ShaderID& id);
            /**
             * @brief Returns the shader with the given name. If the shader does not exist, returns a null shader.
             * @param name The name of the shader.
             * @return The shader.
             * @throws core::ecs::PluginException<MaterialPlugin, ShaderLibrary> If the shader does not exist.
             */
            core::gl::Shader& getShader(const std::string& name);

            private:
            UMap<ShaderID, core::gl::Shader> shaders;  // The shaders in the library.
            UMap<std::string, ShaderID> shaderNames;   // The names of the shaders in the library.
        };
    }  // namespace engine
}  // namespace cobalt