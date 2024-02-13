// Created by tomas on
// 07-02-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ResourceRegistry;
        class SystemManager;

        class SystemParameter {
            public:
            virtual ~SystemParameter() noexcept = default;

            protected:
            SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager) noexcept;

            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
            SystemManager& systemManager;
        };
    }  // namespace core::ecs
}  // namespace cobalt