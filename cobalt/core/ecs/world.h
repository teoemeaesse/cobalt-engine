// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"
#include "core/ecs/system/schedule.h"

namespace cobalt {
    namespace core::ecs {
        class World {
            public:
            enum class DefaultSchedules { Startup, PreUpdate, Update, PostUpdate, PreRender, Render, PostRender, Shutdown };

            /**
             * @brief: Default constructor.
             * @return: World instance.
             */
            World() noexcept;
            /**
             * @brief: Default destructor.
             */
            ~World() noexcept = default;

            /**
             * @brief: Spawn a new entity.
             * @return: Entity instance.
             */
            Entity& spawn() noexcept;
            /**
             * @brief: Kill an entity.
             * @param entity: Entity instance.
             * @return: void
             */
            void kill(const Entity& entity) noexcept;

            /**
             * @brief: Register a component.
             * @tparam ComponentType: Component type.
             * @return: void
             */
            template <typename ComponentType>
            void registerComponent() noexcept {
                componentRegistry.registerComponent<ComponentType>();
            }
            /**
             * @brief: Get a subset of entities' components.
             * @tparam Components...: Components to select for.
             * @return: A vector of tuples of references to components.
             */
            template <typename... Components>
            Vec<Tuple<Components...>> get() const noexcept {
                static_assert((std::is_reference<Components>::value && ...), "All component types must be reference types.");
                return entityRegistry.getMany<Components...>();
            }

            /**
             * @brief: Add a system to the world.
             * @tparam SystemType: System type.
             * @param schedule: Schedule to add the system to.
             * @return: void
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                if (schedules.find(schedule) == schedules.end()) {
                    schedules.emplace(schedule, entityRegistry);
                }
                schedules[schedule].addSystem<SystemType>();
            }
            /**
             * @brief: Run all systems in each schedule, in order.
             * @return: void
             */
            void update() noexcept;

            private:
            EntityRegistry entityRegistry;
            ComponentRegistry componentRegistry;
            UMap<DefaultSchedules, Schedule> schedules;
        };
    }  // namespace core::ecs
}  // namespace cobalt