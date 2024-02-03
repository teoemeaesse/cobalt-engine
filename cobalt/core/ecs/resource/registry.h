// Created by tomas on
// 28-01-2024

#pragma once

#include "core/ecs/resource/resource.h"

namespace cobalt {
    namespace core::ecs {
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
                resources.emplace(Resource::getType<ResourceType>(), ResourceType());
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
                resources.emplace(Resource::getType<ResourceType>(), ResourceType(std::forward<Args>(args)...));
            }

            /**
             * @brief: Get a resource from the registry.
             * @tparam ResourceType: Resource type.
             * @return: Resource reference.
             */
            template <typename ResourceType>
            ResourceType& get() {
                Resource::validate<ResourceType>();
                auto it = resources.find(Resource::getType<ResourceType>());
                if (it == resources.end()) {
                    throw ResourceNotFoundException<ResourceType>();
                }
                return static_cast<ResourceType&>(it->second);
            }
            /**
             * @brief: Get a resource from the registry.
             * @tparam ResourceType: Resource type.
             * @return: Resource reference.
             */
            template <typename ResourceType>
            const ResourceType& get() const {
                Resource::validate<ResourceType>();
                auto it = resources.find(Resource::getType<ResourceType>());
                if (it == resources.end()) {
                    throw ResourceNotFoundException<ResourceType>();
                }
                return static_cast<const ResourceType&>(it->second);
            }

            private:
            UMap<ResourceProperties::Type, Resource> resources;
        };
    }  // namespace core::ecs
}  // namespace cobalt