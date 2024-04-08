// Created by tomas on
// 18-01-2024

#pragma once

#include "core/ecs/event/manager.h"
#include "core/ecs/plugin/bundle.h"
#include "core/ecs/plugin/manager.h"

namespace cobalt {
    namespace core::ecs {
        class World {
            public:
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
                systemManager.addSystem<SystemType>(schedule);
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
                systemManager.addSystem<Params...>(schedule, func);
            }

            /**
             * @brief: Hook a system to an event.
             * @tparam SystemType: System type.
             * @param eventName: Event to hook into.
             * @return: void
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                eventManager.addHook<SystemType>(eventName);
            }
            /**
             * @brief: Hook a system to an event.
             * @tparam Params...: Lambda function parameters.
             * @tparam Func: Lambda function type.
             * @param eventName: Event to hook into.
             * @param func: Lambda function.
             * @return: void
             */
            template <typename... Params, typename Func>
            void addHook(const std::string& eventName, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                eventManager.addHook<Params...>(eventName, func);
            }
            /**
             * @brief: Register an event.
             * @param name: Event name.
             * @param description: Event description.
             * @return: void
             */
            void registerEvent(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief: Trigger an event.
             * @param eventName: Event to trigger.
             * @return: void
             */
            void triggerEvent(const std::string& eventName) noexcept;

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
            ResourceType& getResource() {
                return resourceRegistry.get<ResourceType&>();
            }
            /**
             * @brief: Get a resource.
             * @tparam ResourceType: Resource type.
             * @return: ResourceType reference.
             */
            template <typename ResourceType>
            const ResourceType& getResource() const {
                return resourceRegistry.get<const ResourceType&>();
            }

            /**
             * @brief: Find out if a given plugin is registered. The title must match exactly.
             * @tparam PluginType: Plugin to find.
             * @return: bool
             */
            template <typename PluginType>
            bool isPlugin() const noexcept {
                static_assert(std::is_base_of<Plugin, PluginType>::value, "PluginType must be a subclass of Plugin.");
                static_assert(std::is_default_constructible<PluginType>::value, "PluginType must be default constructible.");
                PluginType plugin;
                return pluginManager.isPlugin(plugin);
            }
            /**
             * @brief: Find out if a given plugin is registered. The title must match exactly.
             * @param title: Plugin title.
             * @return: bool
             */
            bool isPlugin(const std::string& title) const noexcept;
            /**
             * @brief: Add a plugin to the world.
             * @tparam PluginType: Plugin type.
             * @return: void
             */
            template <typename PluginType>
            void addPlugin() noexcept {
                static_assert(std::is_base_of<Plugin, PluginType>::value, "PluginType must be a subclass of Plugin.");
                PluginType plugin;
                pluginManager.addPlugin(plugin);
                plugin.onPlug(*this);
                plugin.log();
            }
            /**
             * @brief: Add a plugin to the world.
             * @tparam PluginType: Plugin type.
             * @tparam Args...: Plugin constructor arguments.
             * @param args: Plugin constructor arguments.
             * @return: void
             */
            template <typename PluginType, typename... Args>
            void addPlugin(Args&&... args) noexcept {
                static_assert(std::is_base_of<Plugin, PluginType>::value, "PluginType must be a subclass of Plugin.");
                PluginType plugin(std::forward<Args>(args)...);
                plugin.onPlug(*this);
                plugin.log();
            }
            /**
             * @brief: Add a plugin bundle to the world.
             * @param bundle: Bundle to add.
             * @return: void
             */
            template <typename BundleType>
            void addBundle() noexcept {
                static_assert(std::is_base_of<core::ecs::Bundle, BundleType>::value, "BundleType must be a subclass of core::ecs::Bundle.");
                BundleType bundle;
                bundle.addPlugins(*this);
            }

            /**
             * @brief: Make a query.
             * @tparam QueryComponents...: The query's components.
             * @return: QueryType instance.
             */
            template <typename... QueryComponents>
            Query<QueryComponents...> makeQuery() noexcept {
                static_assert(sizeof...(QueryComponents) > 0, "Query must have at least one component.");
                return Query<QueryComponents...>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }

            /**
             * @brief: Read a resource.
             * @tparam ResourceType: Resource type.
             * @return: ReadRequest<ResourceType> instance.
             */
            template <typename ResourceType>
            ReadRequest<ResourceType> read() noexcept {
                return ReadRequest<ResourceType>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }
            /**
             * @brief: Write to a resource.
             * @tparam ResourceType: Resource type.
             * @return: WriteRequest<ResourceType> instance.
             */
            template <typename ResourceType>
            WriteRequest<ResourceType> write() noexcept {
                return WriteRequest<ResourceType>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }

            /**
             * @brief: Run the startup schedule.
             * @return: void
             */
            void startup();
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
            PluginManager pluginManager;
            SystemManager systemManager;
            EventManager eventManager;
        };
    }  // namespace core::ecs
}  // namespace cobalt