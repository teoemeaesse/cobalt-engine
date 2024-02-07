// Created by tomas on
// 07-02-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ResourceRegistry;

        class SystemParameter {
            public:
            virtual ~SystemParameter() noexcept = default;

            protected:
            SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry) noexcept
                : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry) {}

            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt