// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/properties.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        class Component {
            public:
            /** @brief: Validate a set of component types.
             * @tparam Types...: Component types.
             * @return: True if the component type is valid.
             */
            template <typename... Types>
            static constexpr bool validate() {
                static_assert((std::is_base_of<Component, Types>::value && ...), "All types must be components.");
                static_assert((std::is_default_constructible<Types>::value && ...), "All types must be default constructible.");
                static_assert((std::is_copy_constructible<Types>::value && ...), "All types must be copy constructible.");
                return true;
            }

            /** @brief: Get the component's type. This is a unique identifier, lazy-generated based on the component class' name.
             * @return: Component type identifier.
             */
            virtual const ComponentProperties::Type getType() noexcept;
            /** @brief: Get the component's type. This is a unique identifier, generated at compile time based on the component class' name.
             * @tparam T: Component type.
             * @return: Component type identifier.
             */
            template <typename T>
            static const ComponentProperties::Type getType() noexcept {
                static const ComponentProperties::Type type = typeid(T).hash_code();
                return type;
            }

            /** @brief: Get the component's type name.
             * @return: Component type name.
             */
            virtual const std::string& getTypeName() noexcept;

            static inline const std::string demangle(const char* name) noexcept {
                int status = 42;
                std::unique_ptr<char, void (*)(void*)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
                return (status == 0) ? res.get() : name;
            }
            /** @brief: Get the component's type name.
             * @tparam T: Component type.
             * @return: Component type name.
             */
            template <typename T>
            static const std::string& getTypeName() noexcept {
                static const std::string typeName = demangle(typeid(T).name());
                return typeName;
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt