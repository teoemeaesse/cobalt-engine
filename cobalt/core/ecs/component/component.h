/**
 * @file component.h
 * @brief Defines the Component class, which is the base class for all components in the ECS.
 * @author Tomás Marques
 * @date 18-01-2024
 */

#pragma once

#include "core/ecs/properties.h"

namespace cobalt {
    static inline const std::string demangle(const char* name) noexcept;

    namespace core::ecs {
        /**
         * @brief Base class for all components in the ECS. Provides type validation and identification.
         * Every component must inherit from this class and be:
         * - A child of Component;
         * - Default constructible;
         * - Copy constructible.
         */
        class Component {
            public:
            /**
             * @brief Validate a set of component types.
             * @tparam ComponentTypes... The component types.
             * @return True if the component type is valid, false otherwise.
             */
            template <typename... ComponentTypes>
            static constexpr bool validate() {
                static_assert((std::is_base_of<Component, ComponentTypes>::value && ...), "All ComponentTypes must be components.");
                static_assert(((std::is_copy_constructible<ComponentTypes>::value || std::is_move_constructible<ComponentTypes>::value) && ...),
                              "All ComponentTypes must be copy constructible.");
                return true;
            }

            /**
             * @brief Get the component's type. This is a unique identifier, lazy-generated based on the component class's name.
             * @return Component type identifier.
             */
            virtual const ComponentProperties::Type getType() const noexcept;
            /**
             * @brief Get the component's type. This is a unique identifier, generated at compile time based on the component class's name.
             * @tparam ComponentType The component type.
             * @return The component's type identifier.
             */
            template <typename ComponentType>
            static const ComponentProperties::Type getType() noexcept {
                static const ComponentProperties::Type type = typeid(ComponentType).hash_code();
                return type;
            }

            /**
             * @brief Get the component type's name.
             * @return The component type's name.
             */
            virtual const std::string& getTypeName() const noexcept;
            /**
             * @brief Get the component type's name.
             * @tparam ComponentType The component type.
             * @return The component type's name.
             */
            template <typename ComponentType>
            static const std::string& getTypeName() noexcept {
                static const std::string typeName = demangle(typeid(ComponentType).name());
                return typeName;
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt