// Created by tomas on
// 03-02-2024

#pragma once

#include "core/ecs/resource/registry.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        class SystemManager;

        /**
         * @brief Resource request. Facilitates read-only access to resources.
         * @tparam ResourceType: Resource type.
         */
        template <typename ResourceType>
        class ReadRequest : SystemParameter {
            public:
            /**
             * @brief Constructor.
             * @param entityRegistry Entity registry. Unused.
             * @param resourceRegistry Resource registry.
             * @param systemManager System manager. Unused.
             * @param eventManager Event manager. Unused.
             * @return Read request instance.
             */
            ReadRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager, EventManager& eventManager)
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager),
                  resource(resourceRegistry.get<const ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief Destroys the request.
             */
            ~ReadRequest() noexcept = default;

            /**
             * @brief Dereferences into the underlying resource directly.
             * @return The requested resource.
             */
            const ResourceType& operator*() const { return resource; }
            /**
             * @brief Dereferences into the underlying resource directly.
             * @return The requested resource.
             */
            const ResourceType* operator->() const { return &resource; }

            private:
            const ResourceType& resource;
        };

        /**
         * @brief Resource request. Facilitates read-write access to resources.
         * @tparam ResourceType: Resource type.
         */
        template <typename ResourceType>
        class WriteRequest : SystemParameter {
            public:
            /**
             * @brief Constructor.
             * @param entityRegistry Entity registry. Unused.
             * @param resourceRegistry Resource registry.
             * @param systemManager System manager. Unused.
             * @param eventManager Event manager. Unused.
             * @return Write request instance.
             */
            explicit WriteRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                                  EventManager& eventManager)
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager), resource(resourceRegistry.get<ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief Destroys the request.
             */
            ~WriteRequest() noexcept = default;

            /**
             * @brief Dereferences into the underlying resource directly.
             * @return The requested resource.
             */
            ResourceType& operator*() { return resource; }
            /**
             * @brief Dereferences into the underlying resource directly.
             * @return The requested resource.
             */
            ResourceType* operator->() { return &resource; }

            private:
            ResourceType& resource;
        };
    }  // namespace core::ecs
}  // namespace cobalt