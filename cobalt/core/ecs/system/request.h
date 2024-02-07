// Created by tomas on
// 03-02-2024

#pragma once

#include "core/ecs/resource/registry.h"
#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Resource request. Facilitates read-only access to resources.
         * @tparam ResourceType: Resource type.
         */
        template <typename ResourceType>
        class ReadRequest : SystemParameter {
            public:
            /**
             * @brief: Constructor.
             * @param entityRegistry: Entity registry. Unused.
             * @param resourceRegistry: Resource registry.
             * @return: Read request instance.
             */
            ReadRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept
                : SystemParameter(entityRegistry, resourceRegistry), resource(resourceRegistry.get<const ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief: Destructor.
             * @return: void
             */
            ~ReadRequest() noexcept = default;

            /**
             * @brief: Get resource.
             * @return: Resource.
             */
            const ResourceType& get() const { return resource; }

            private:
            const ResourceType& resource;
        };

        /**
         * @brief: Resource request. Facilitates read-write access to resources.
         * @tparam ResourceType: Resource type.
         */
        template <typename ResourceType>
        class WriteRequest : SystemParameter {
            public:
            /**
             * @brief: Constructor.
             * @param entityRegistry: Entity registry. Unused.
             * @param resourceRegistry: Resource registry.
             * @return: Write request instance.
             */
            explicit WriteRequest(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept
                : SystemParameter(entityRegistry, resourceRegistry), resource(resourceRegistry.get<ResourceType&>()) {
                Resource::validate<ResourceType>();
            }
            /**
             * @brief: Destructor.
             * @return: void
             */
            ~WriteRequest() noexcept = default;

            /**
             * @brief: Get resource.
             * @return: Resource.
             */
            ResourceType& get() { return resource; }

            private:
            ResourceType& resource;
        };
    }  // namespace core::ecs
}  // namespace cobalt