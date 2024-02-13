// Created by tomas on
// 28-01-2024

#pragma once

#include "core/ecs/resource/resource.h"
#include "core/exceptions/ecs_exception.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Resource registry. Responsible for managing ECS resources. Resources are globally unique and accessible by systems.
         */
        class ResourceRegistry {
            public:
            ResourceRegistry() noexcept = default;
            ~ResourceRegistry() noexcept = default;

            /**
             * @brief: Add a resource to the registry.
             * @tparam ResourceType: Resource type.
             * @return: void
             */
            template <typename ResourceType>
            void add() noexcept {
                Resource::validate<ResourceType>();
                static_assert(std::is_default_constructible<ResourceType>::value, "Resource must be default constructible.");
                const auto type = Resource::getType<ResourceType>();
                resources.erase(type);
                resources.emplace(type, Move(createScope<ResourceType>()));
            }
            /**
             * @brief: Add a resource to the registry.
             * @tparam ResourceType: Resource type.
             * @tparam Args...: Resource constructor arguments.
             * @param: args: Resource constructor arguments.
             * @return: void
             */
            template <typename ResourceType, typename... Args>
            void add(Args&&... args) noexcept {
                Resource::validate<ResourceType>();
                static_assert(std::is_constructible<ResourceType, Args...>::value, "Resource must be constructible with the given arguments.");
                const auto type = Resource::getType<ResourceType>();
                resources.erase(type);
                resources.emplace(type, Move(createScope<ResourceType>(std::forward<Args>(args)...)));
            }
            /**
             * @brief: Move a resource into the registry.
             * @param resource: Resource.
             * @return: void
             */
            void add(Scope<Resource>&& resource) noexcept;

            /**
             * @brief: Get a resource from the registry.
             * @tparam ResourceRef: Resource reference.
             * @return: Resource reference.
             */
            template <typename ResourceRef>
            ResourceRef get() {
                try {
                    return *dynamic_cast<RemoveConstRef<ResourceRef>*>(resources.at(Resource::getType<RemoveConstRef<ResourceRef>>()).get());
                } catch (const std::out_of_range& e) {
                    throw ResourceNotFoundException<RemoveConstRef<ResourceRef>>();
                }
            }
            /**
             * @brief: Get a resource from the registry.
             * @tparam ResourceRef: Resource reference.
             * @return: Resource reference.
             */
            template <typename ResourceRef>
            ResourceRef get() const {
                try {
                    return *dynamic_cast<RemoveConstRef<ResourceRef>*>(resources.at(Resource::getType<RemoveConstRef<ResourceRef>>()).get());
                } catch (const std::out_of_range& e) {
                    throw ResourceNotFoundException<RemoveConstRef<ResourceRef>>();
                }
            }

            private:
            UMap<ResourceProperties::Type, Scope<Resource>> resources;
        };
    }  // namespace core::ecs
}  // namespace cobalt