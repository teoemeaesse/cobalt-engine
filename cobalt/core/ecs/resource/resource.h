/**
 * @file resource.h
 * @brief A Resource is an ECS element consisting of a piece of structured data that can be shared between systems.
 * @author Tomás Marques
 * @date 03-02-2024
 */

#pragma once

#include "core/ecs/properties.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief A Resource is an ECS element consisting of a piece of structured data that can be shared between systems.
         * Resources are globally unique (within the scope of a World) and accessible by all systems via ReadRequest's and WriteRequest's.
         */
        class Resource {
            public:
            /**
             * @brief Validates a resource type.
             * @tparam ResourceType The resource type.
             * @return True if the resource type is valid, false otherwise.
             */
            template <typename ResourceType>
            static inline constexpr bool validate() {
                static_assert(std::is_base_of<Resource, ResourceType>::value, "Type must be a resource.");
                return true;
            }

            /**
             * @brief Create a resource. Overload this function in your resources!
             * @return The new resource.
             */
            static Resource create() noexcept { return Resource(); }

            /**
             * @brief Default constructor.
             */
            Resource() noexcept = default;
            /**
             * @brief Default destructor.
             */
            virtual ~Resource() noexcept = default;
            /**
             * @brief Copy constructor.
             * @param other The resource to copy.
             */
            Resource(const Resource& other) noexcept = default;
            /**
             * @brief Move constructor.
             * @param other The resource to move.
             */
            Resource(Resource&& other) noexcept = default;
            /**
             * @brief Copy assignment operator.
             * @param other The resource to copy.
             * @return A reference to this.
             */
            Resource& operator=(const Resource& other) noexcept = default;
            /**
             * @brief Move assignment operator.
             * @param other The resource to move.
             * @return A reference to this.
             */
            Resource& operator=(Resource&& other) = default;

            /**
             * @brief Gets the resource's type. This is a unique identifier, lazy-generated based on the resource class's name.
             * @return The resource type identifier.
             */
            virtual const ResourceProperties::Type getType() const noexcept;
            /**
             * @brief Gets the resource's type. This is a unique identifier, generated at compile time based on the resource class's name.
             * @tparam ResourceType The resource type.
             * @return The resource type identifier.
             */
            template <typename ResourceType>
            static const ResourceProperties::Type getType() noexcept {
                static const ResourceProperties::Type type = typeid(ResourceType).hash_code();
                return type;
            }

            /**
             * @brief Gets the resource's type name.
             * @return The resource's type name.
             */
            virtual const std::string& getTypeName() const noexcept;
            /**
             * @brief Gets the resource's type name.
             * @tparam ResourceType The resource type.
             * @return The resource type name.
             */
            template <typename ResourceType>
            static const std::string& getTypeName() noexcept {
                static const std::string typeName = demangle(typeid(ResourceType).name());
                return typeName;
            }
        };
    }  // namespace core::ecs
}  // namespace cobalt