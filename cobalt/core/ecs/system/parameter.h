// Created by tomas on
// 07-02-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ResourceRegistry;
        class SystemManager;
        class EventManager;

        class SystemParameter {
            public:
            virtual ~SystemParameter() noexcept = default;

            protected:
            SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                            EventManager& eventManager) noexcept;

            EntityRegistry& entityRegistry;
            ResourceRegistry& resourceRegistry;
            SystemManager& systemManager;
            EventManager& eventManager;
        };
    }  // namespace core::ecs
}  // namespace cobalt