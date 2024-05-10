/**
 * @file world.h
 * @brief An ECS world that holds entities, components, resources, systems, events, and plugins. It is responsible for managing the ECS architecture.
 * @author Tomás Marques
 * @date 18-01-2024
 */

#pragma once

#include "core/ecs/event/manager.h"
#include "core/ecs/plugin/bundle.h"
#include "core/ecs/plugin/manager.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief The ECS world is the primary interface with the ECS. It should be used for all ECS operations.
         */
        class World {
            public:
            /**
             * @brief Create a new world.
             * @return World instance.
             */
            World() noexcept;
            /**
             * @brief Destroy the world. Releases all resources allocated for the ECS resources.
             */
            ~World() noexcept = default;

            /**
             * @brief Spawn a new entity.
             * @return Entity instance.
             */
            Entity& spawn() noexcept;

            /**
             * @brief Register a component.
             * @tparam ComponentType The component type.
             */
            template <typename ComponentType>
            void registerComponent() noexcept {
                componentRegistry.registerComponent<ComponentType>();
            }

            /**
             * @brief Add a system to the world.
             * @tparam SystemType The system type.
             * @param schedule Schedule to add the system to.
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systemManager.addSystem<SystemType>(schedule);
            }
            /**
             * @brief Add a system to the world.
             * @tparam Params... Lambda function parameter types.
             * @tparam Func Lambda function type.
             * @param schedule Schedule to add the system to.
             * @param func Lambda function.
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systemManager.addSystem<Params...>(schedule, func);
            }

            /**
             * @brief Hook a system to an event.
             * @tparam SystemType The system type.
             * @param eventName Event to hook into.
             */
            template <typename SystemType>
            void addHook(const std::string& eventName) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                eventManager.addHook<SystemType>(eventName);
            }
            /**
             * @brief Hook a system to an event.
             * @tparam Params... Lambda function parameter types.
             * @tparam Func Lambda function type.
             * @param eventName The event to hook into.
             * @param func Lambda function.
             */
            template <typename... Params, typename Func>
            void addHook(const std::string& eventName, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                eventManager.addHook<Params...>(eventName, func);
            }
            /**
             * @brief Register an event.
             * @param name The event's name.
             * @param description The event's description.
             */
            void registerEvent(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief Trigger an event.
             * @param eventName The event to trigger.
             */
            void triggerEvent(const std::string& eventName) noexcept;

            /**
             * @brief Add a unique resource.
             * @tparam ResourceType The resource type.
             */
            template <typename ResourceType>
            void addResource() noexcept {
                resourceRegistry.add<ResourceType>();
            }
            /**
             * @brief Add a resource with constructor arguments.
             * @tparam ResourceType The resource type.
             * @tparam Args... Resource constructor argument types.
             * @param args Resource constructor arguments.
             */
            template <typename ResourceType, typename... Args>
            void addResource(Args&&... args) noexcept {
                resourceRegistry.add<ResourceType>(std::forward<Args>(args)...);
            }

            /**
             * @brief Get a mutable resource.
             * @tparam ResourceType The resource type.
             * @return ResourceType The requested resource.
             */
            template <typename ResourceType>
            ResourceType& getResource() {
                return resourceRegistry.get<ResourceType&>();
            }
            /**
             * @brief Get a const resource.
             * @tparam ResourceType Resource type.
             * @return ResourceType The requested resource.
             */
            template <typename ResourceType>
            const ResourceType& getResource() const {
                return resourceRegistry.get<const ResourceType&>();
            }

            /**
             * @brief Find out if a given plugin is registered. The title must match exactly.
             * @tparam PluginType The plugin to find.
             * @return True if the plugin is registered, false otherwise.
             */
            template <typename PluginType>
            bool isPlugin() const noexcept {
                static_assert(std::is_base_of<Plugin, PluginType>::value, "PluginType must be a subclass of Plugin.");
                static_assert(std::is_default_constructible<PluginType>::value, "PluginType must be default constructible.");
                PluginType plugin;
                return pluginManager.isPlugin(plugin);
            }
            /**
             * @brief Find out if a given plugin is registered. The title must match exactly.
             * @param title The plugin's title.
             * @return True if the plugin is registered, false otherwise.
             */
            bool isPlugin(const std::string& title) const noexcept;
            /**
             * @brief Add a plugin to the world.
             * @tparam PluginType The plugin type.
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
             * @brief Add a plugin to the world.
             * @tparam PluginType The plugin type.
             * @tparam Args... The plugin's constructor argument types.
             * @param args The plugin's constructor arguments.
             */
            template <typename PluginType, typename... Args>
            void addPlugin(Args&&... args) noexcept {
                static_assert(std::is_base_of<Plugin, PluginType>::value, "PluginType must be a subclass of Plugin.");
                PluginType plugin(std::forward<Args>(args)...);
                plugin.onPlug(*this);
                plugin.log();
            }
            /**
             * @brief Add a plugin bundle to the world.
             * @tparam BundleType The bundle type.
             * @param bundle The bundle to add.
             */
            template <typename BundleType>
            void addBundle() noexcept {
                static_assert(std::is_base_of<core::ecs::Bundle, BundleType>::value, "BundleType must be a subclass of core::ecs::Bundle.");
                BundleType bundle;
                bundle.addPlugins(*this);
            }

            /**
             * @brief Make a query.
             * @tparam QueryComponents... The query's component types.
             * @return The created query.
             */
            template <typename... QueryComponents>
            Query<QueryComponents...> makeQuery() noexcept {
                static_assert(sizeof...(QueryComponents) > 0, "Query must have at least one component.");
                return Query<QueryComponents...>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }

            /**
             * @brief Read a resource.
             * @tparam ResourceType The resource type.
             * @return ReadRequest<ResourceType> The read request.
             */
            template <typename ResourceType>
            ReadRequest<ResourceType> read() noexcept {
                return ReadRequest<ResourceType>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }
            /**
             * @brief Write to a resource.
             * @tparam ResourceType The resource type.
             * @return WriteRequest<ResourceType> The write request.
             */
            template <typename ResourceType>
            WriteRequest<ResourceType> write() noexcept {
                return WriteRequest<ResourceType>(entityRegistry, resourceRegistry, systemManager, eventManager);
            }

            /**
             * @brief Run the startup schedule.
             */
            void startup();
            /**
             * @brief Run the pre-update, update, and post-update schedules.
             */
            void update() noexcept;
            /**
             * @brief Run the pre-render, render, and post-render schedules.
             */
            void render() noexcept;
            /**
             * @brief Run the shutdown schedule.
             */
            void shutdown() noexcept;

            private:
            EntityRegistry entityRegistry;        ///< EntityRegistry where all entities are stored.
            ComponentRegistry componentRegistry;  ///< ComponentRegistry where all components are stored.
            ResourceRegistry resourceRegistry;    ///< ResourceRegistry where all resources are stored.
            PluginManager pluginManager;          ///< PluginManager where all plugins are stored.
            SystemManager systemManager;          ///< SystemManager where all systems are stored.
            EventManager eventManager;            ///< EventManager where all events are stored.
        };
    }  // namespace core::ecs
}  // namespace cobalt