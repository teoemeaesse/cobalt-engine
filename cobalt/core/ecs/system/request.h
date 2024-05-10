/**
 * @file request.h
 * @brief A request is a SystemParameter that allows systems to access resources in a read-only or read-write manner.
 * @author Tomás Marques
 * @date 03-02-2024
 */

#pragma once

#include "core/ecs/resource/registry.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        class SystemManager;

        /**
         * @brief A ReadRequest provides read-only access to a resource.
         * @tparam ResourceType The Resource type to read.
         */
        template <typename ResourceType>
        class ReadRequest : SystemParameter {
            public:
            /**
             * @brief Creates a new ReadRequest.
             * @param entityRegistry The EntityRegistry that the request will run on. Unused.
             * @param resourceRegistry The ResourceRegistry that the request will run on.
             * @param systemManager The SystemManager that the request will run on. Unused.
             * @param eventManager The EventManager that the request will run on. Unused.
             */
            ReadRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager, EventManager& eventManager)
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager),
                  resource(resourceRegistry.get<const ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief Default destructor.
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
            const ResourceType& resource;  ///< The requested resource.
        };

        /**
         * @brief A WriteRequest provides read-write access to a resource.
         * @tparam ResourceType The Resource type to write.
         */
        template <typename ResourceType>
        class WriteRequest : SystemParameter {
            public:
            /**
             * @brief Creates a new WriteRequest.
             * @param entityRegistry The EntityRegistry that the request will run on. Unused.
             * @param resourceRegistry The ResourceRegistry that the request will run on.
             * @param systemManager The SystemManager that the request will run on. Unused.
             * @param eventManager The EventManager that the request will run on. Unused.
             */
            explicit WriteRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                                  EventManager& eventManager)
                : SystemParameter(entityRegistry, resourceRegistry, systemManager, eventManager), resource(resourceRegistry.get<ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief Default destructor.
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
            ResourceType& resource;  ///< The requested resource.
        };
    }  // namespace core::ecs
}  // namespace cobalt