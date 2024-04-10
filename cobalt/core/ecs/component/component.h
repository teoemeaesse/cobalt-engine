// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/properties.h"
#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        class Component {
            public:
            /**
             * @brief Validate a set of component types.
             * @tparam Components...: Component types.
             * @return True if the component type is valid.
             */
            template <typename... Components>
            static constexpr bool validate() {
                static_assert((std::is_base_of<Component, Components>::value && ...), "All types must be components.");
                static_assert((std::is_default_constructible<Components>::value && ...), "All types must be default constructible.");
                static_assert((std::is_copy_constructible<Components>::value && ...), "All types must be copy constructible.");
                return true;
            }

            /**
             * @brief Get the component's type. This is a unique identifier, lazy-generated based on the component class' name.
             * @return Component type identifier.
             */
            virtual const ComponentProperties::Type getType() const noexcept;
            /**
             * @brief Get the component's type. This is a unique identifier, generated at compile time based on the component class' name.
             * @tparam ComponentType: Component type.
             * @return Component type identifier.
             */
            template <typename ComponentType>
            static const ComponentProperties::Type getType() noexcept {
                static const ComponentProperties::Type type = typeid(ComponentType).hash_code();
                return type;
            }

            /**
             * @brief Get the component's type name.
             * @return Component type name.
             */
            virtual const std::string& getTypeName() const noexcept;
            /**
             * @brief Get the component's type name.
             * @tparam ComponentType: Component type.
             * @return Component type name.
             */
            template <typename ComponentType>
            static const std::string& getTypeName() noexcept {
                static const std::string typeName = demangle(typeid(ComponentType).name());
                return typeName;
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt