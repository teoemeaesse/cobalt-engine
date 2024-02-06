// Created by tomas on
// 03-02-2024

#pragma once

#include "core/ecs/resource/registry.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief: Resource request interface.
         */
        class RequestInterface {
            public:
            /**
             * @brief: Destructor.
             * @return: void
             */
            virtual ~RequestInterface() noexcept = default;

            protected:
            /**
             * @brief: Default constructor.
             * @return: RequestInterface instance.
             */
            RequestInterface() noexcept = default;
        };

        /**
         * @brief: Resource request. Facilitates read-only access to resources.
         * @tparam ResourceType: Resource type.
         */
        template <typename ResourceType>
        class ReadRequest : RequestInterface {
            public:
            /**
             * @brief: Constructor.
             * @param resourceRegistry: Resource registry.
             * @return: Read request instance.
             */
            explicit ReadRequest(const ResourceRegistry& resourceRegistry) noexcept : resource(resourceRegistry.get<const ResourceType&>()) {
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
        class WriteRequest : RequestInterface {
            public:
            /**
             * @brief: Constructor.
             * @param resourceRegistry: Resource registry.
             * @return: Write request instance.
             */
            explicit WriteRequest(const ResourceRegistry& resourceRegistry) noexcept : resource(resourceRegistry.get<ResourceType&>()) {
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