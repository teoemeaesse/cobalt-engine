// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/component/registry.h"
#include "core/ecs/entity/registry.h"
#include "core/ecs/plugin/plugin.h"
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
             * @brief: Register a component.
             * @tparam ComponentType: Component type.
             * @return: void
             */
            template <typename ComponentType>
            void registerComponent() noexcept {
                componentRegistry.registerComponent<ComponentType>();
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
                schedules[schedule]->addSystem<SystemType>();
            }
            /**
             * @brief: Add a system to the world.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param schedule: Schedule to add the system to.
             * @param func: Lambda function.
             * @return: void
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                schedules[schedule]->addSystem<Params...>(func);
            }

            /**
             * @brief: Add a unique resource.
             * @tparam ResourceType: Resource type.
             * @return: void
             */
            template <typename ResourceType>
            void addResource() noexcept {
                resourceRegistry.add<ResourceType>();
            }
            /**
             * @brief: Add a resource with constructor arguments.
             * @tparam ResourceType: Resource type.
             * @tparam Args...: Resource constructor arguments.
             * @param args: Resource constructor arguments.
             * @return: void
             */
            template <typename ResourceType, typename... Args>
            void addResource(Args&&... args) noexcept {
                resourceRegistry.add<ResourceType>(std::forward<Args>(args)...);
            }

            /**
             * @brief: Get a resource.
             * @tparam ResourceType: Resource type.
             * @return: ResourceType reference.
             */
            template <typename ResourceType>
            ResourceType& getResource() noexcept {
                return resourceRegistry.get<ResourceType>();
            }
            /**
             * @brief: Get a resource.
             * @tparam ResourceType: Resource type.
             * @return: ResourceType reference.
             */
            template <typename ResourceType>
            const ResourceType& getResource() const noexcept {
                return resourceRegistry.get<ResourceType>();
            }

            /**
             * @brief: Add a plugin to the world.
             * @param plugin: Plugin instance.
             * @return: void
             */
            void addPlugin(const Plugin& plugin) noexcept;

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
            EntityRegistry entityRegistry;
            ComponentRegistry componentRegistry;
            ResourceRegistry resourceRegistry;
            UMap<DefaultSchedules, Scope<Schedule>> schedules;
        };
    }  // namespace core::ecs
}  // namespace cobalt