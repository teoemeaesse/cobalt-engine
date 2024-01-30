// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"

namespace cobalt {
    namespace core::ecs {
        class World {
            public:
            /** @brief: Default constructor.
             * @return: World instance.
             */
            World() noexcept;
            /** @brief: Default destructor.
             */
            ~World() = default;

            /** @brief: Create a new entity.
             * @return: Entity instance.
             */
            Entity& createEntity() noexcept;

            /** @brief: Destroy an entity.
             * @param entity: Entity instance.
             */
            void destroyEntity(const Entity& entity) noexcept;

            template <typename... Components>
            Vec<Tuple<Components...>> get() const noexcept {
                static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");
                return entityRegistry.get<Components...>();
            }

            private:
            EntityRegistry entityRegistry;
            ComponentRegistry componentRegistry;
        };
    }  // namespace core::ecs
}  // namespace cobalt