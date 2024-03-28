// Created by tomas on
// 03-02-2024

#pragma once

#include "core/ecs/properties.h"

namespace cobalt {
    namespace core::ecs {
        class Resource {
            public:
            /**
             * @brief: Validate a resource type.
             * @tparam ResourceType: Resource type.
             * @return: True if the resource type is valid.
             */
            template <typename ResourceType>
            static inline constexpr bool validate() {
                static_assert(std::is_base_of<Resource, ResourceType>::value, "Type must be a resource.");
                return true;
            }

            /**
             * @brief: Default constructor.
             * @return: Instance of Resource.
             */
            Resource() noexcept = default;
            /**
             * @brief: Default destructor.
             * @return: void
             */
            virtual ~Resource() noexcept = default;
            /**
             * @brief: Copy constructor.
             * @param: Resource to copy.
             * @return: Instance of Resource.
             */
            Resource(const Resource&) noexcept = default;
            /**
             * @brief: Move constructor.
             * @param: Resource to move.
             * @return: Instance of Resource.
             */
            Resource(Resource&&) noexcept = default;
            /**
             * @brief: Copy assignment operator.
             * @param: Resource to copy.
             * @return: Resource reference.
             */
            Resource& operator=(const Resource&) noexcept = default;
            /**
             * @brief: Move assignment operator.
             * @param: Resource to move.
             * @return: Resource reference.
             */
            Resource& operator=(Resource&&) = default;

            /**
             * @brief: Get the resource's type. This is a unique identifier, lazy-generated based on the resource class' name.
             * @return: Resource type identifier.
             */
            virtual const ResourceProperties::Type getType() const noexcept;
            /**
             * @brief: Get the resource's type. This is a unique identifier, generated at compile time based on the resource class' name.
             * @tparam ResourceType: Resource type.
             * @return: Resource type identifier.
             */
            template <typename ResourceType>
            static const ResourceProperties::Type getType() noexcept {
                static const ResourceProperties::Type type = typeid(ResourceType).hash_code();
                return type;
            }

            /**
             * @brief: Get the resource's type name.
             * @return: Resource type name.
             */
            virtual const std::string& getTypeName() const noexcept;
            /**
             * @brief: Get the resource's type name.
             * @tparam ResourceType: Resource type.
             * @return: Resource type name.
             */
            template <typename ResourceType>
            static const std::string& getTypeName() noexcept {
                static const std::string typeName = demangle(typeid(ResourceType).name());
                return typeName;
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt