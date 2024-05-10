/**
 * @file registry.h
 * @brief Storage for every resource in the ECS.
 * @author Tomás Marques
 * @date 28-01-2024
 */

#pragma once

#include "core/ecs/exception.h"
#include "core/ecs/resource/resource.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief Stores and manages all the resources in the ECS.
         * Resources are globally unique and accessible by systems.
         */
        class ResourceRegistry {
            public:
            /**
             * @brief Default constructor.
             */
            ResourceRegistry() noexcept = default;
            /**
             * @brief Default destructor.
             */
            ~ResourceRegistry() noexcept = default;

            /**
             * @brief Adds a resource to the registry.
             * @tparam ResourceType The resource type.
             */
            template <typename ResourceType>
            void add() noexcept {
                Resource::validate<ResourceType>();
                static_assert(std::is_default_constructible<ResourceType>::value, "Resource must be default constructible.");
                const auto type = Resource::getType<ResourceType>();
                resources.erase(type);
                resources.emplace(type, Move(CreateScope<ResourceType>()));
            }
            /**
             * @brief Adds a resource to the registry.
             * @tparam ResourceType The resource type.
             * @tparam Args... The resource constructor argument types.
             * @param args The resource constructor arguments.
             */
            template <typename ResourceType, typename... Args>
            void add(Args&&... args) noexcept {
                Resource::validate<ResourceType>();
                static_assert(std::is_constructible<ResourceType, Args...>::value, "Resource must be constructible with the given arguments.");
                const auto type = Resource::getType<ResourceType>();
                resources.erase(type);
                resources.emplace(type, Move(CreateScope<ResourceType>(std::forward<Args>(args)...)));
            }

            /**
             * @brief Gets a resource from the registry.
             * @tparam ResourceRef The resource type reference.
             * @return A mutable reference to the resource.
             */
            template <typename ResourceRef>
            ResourceRef get() {
                try {
                    return *dynamic_cast<RemoveConstRef<ResourceRef>*>(resources.at(Resource::getType<RemoveConstRef<ResourceRef>>()).get());
                } catch (const std::out_of_range& e) {
                    throw ResourceNotFoundException<RemoveConstRef<ResourceRef>, ResourceRegistry>();
                }
            }
            /**
             * @brief Gets a resource from the registry.
             * @tparam ResourceRef The resource type reference.
             * @return A const reference to the resource.
             */
            template <typename ResourceRef>
            ResourceRef get() const {
                try {
                    return *dynamic_cast<RemoveConstRef<ResourceRef>*>(resources.at(Resource::getType<RemoveConstRef<ResourceRef>>()).get());
                } catch (const std::out_of_range& e) {
                    throw ResourceNotFoundException<RemoveConstRef<ResourceRef>, ResourceRegistry>();
                }
            }

            private:
            UMap<ResourceProperties::Type, Scope<Resource>> resources;  ///< The resources in the registry.
        };
    }  // namespace core::ecs
}  // namespace cobalt