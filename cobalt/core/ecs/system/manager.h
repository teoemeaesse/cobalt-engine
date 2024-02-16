// Created by tomas on
// 13-02-2024

#pragma once

#include "core/ecs/system/registry.h"

namespace cobalt {
    namespace core::ecs {
        enum class DefaultSchedules { Startup, PreUpdate, Update, PostUpdate, PreRender, Render, PostRender, Shutdown };

        class EntityRegistry;
        class ResourceRegistry;
        class EventManager;

        class SystemManager {
            public:
            /**
             * @brief: Default constructor.
             * @param entityRegistry: Entity registry.
             * @param resourceRegistry: Resource registry.
             * @param eventManager: Event manager.
             * @return: SystemManager instance.
             */
            SystemManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, EventManager& eventManager) noexcept;

            /**
             * @brief: Add a system to a schedule.
             * @tparam SystemType: System type.
             * @param schedule: Schedule to add the system to.
             * @return: void
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems[schedule]->addSystem<SystemType>();
            }
            /**
             * @brief: Add a system to a schedule.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param schedule: Schedule to add the system to.
             * @param func: Lambda function.
             * @return: void
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systems[schedule]->addSystem<Params...>(func);
            }

            /**
             * @brief: Run the startup schedule.
             * @return: void
             */
            void startup() noexcept;
            /**
             * @brief: Run the pre-update, update, and post-update schedules.
             * @return: void
             */
            void update() noexcept;
            /**
             * @brief: Run the pre-render, render, and post-render schedules.
             * @return: void
             */
            void render() noexcept;
            /**
             * @brief: Run the shutdown schedule.
             * @return: void
             */
            void shutdown() noexcept;

            private:
            UMap<DefaultSchedules, Scope<SystemRegistry>> systems;
        };
    }  // namespace core::ecs
}  // namespace cobalt