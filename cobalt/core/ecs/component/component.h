// Created by tomas on
// 18-01-2024

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        class Component {
            public:
            using ID = uint64;    // Component ID - unique between all components.
            using Type = uint64;  // Component type - unique between different component types.

            /** @brief: Validate a component type.
             * @tparam T: Component type.
             * @return: True if the component type is valid.
             */
            template <typename T>
            static constexpr bool validateComponent() {
                static_assert(std::is_base_of<Component, T>::value, "T must be a component.");
                static_assert(std::is_default_constructible<T>::value, "T must be default constructible.");
                static_assert(std::is_copy_constructible<T>::value, "T must be copy constructible.");
                return true;
            }

            /** @brief: Default constructor.
             * @param id: Component ID.
             * @return: Component instance.
             */
            Component(const ID id) noexcept;

            /** @brief: Get the component's type. This is a unique identifier, lazy-generated based on the component class' name.
             * @return: Component type identifier.
             */
            virtual const Type getType() noexcept;

            /**
             * @brief: Get the component's type. This is a unique identifier, generated at compile time based on the component class' name.
             * @tparam T: Component type.
             * @return: Component type identifier.
             */
            template <typename T>
            static const Type getType() noexcept {
                validateComponent<T>();
                const T component(0);
                return component.getType();
            }

            private:
            Type type;
            ID id;
        };
    }  // namespace core::ecs
}  // namespace cobalt