/**
 * @file manager.h
 * @brief A manager for System's allowing for easy System creation and execution.
 * @author Tomás Marques
 * @date 13-02-2024
 */

#pragma once

#include "core/ecs/system/registry.h"

namespace cobalt {
    namespace core::ecs {
        enum class DefaultSchedules { Startup, PreUpdate, Update, PostUpdate, PreRender, Render, PostRender, Shutdown };

        class EntityRegistry;
        class ResourceRegistry;
        class EventManager;

        /**
         * @brief A SystemManager is responsible for managing Systems and executing them in the correct order.
         * Systems are executed according to their scheduling in the following order:
         * 1. Startup
         * 2. PreUpdate
         * 3. Update
         * 4. PostUpdate
         * 5. PreRender
         * 6. Render
         * 7. PostRender
         * 8. Shutdown
         *
         * TODO: Add a way to add custom schedules.
         * @see DefaultSchedules
         */
        class SystemManager {
            public:
            /**
             * @brief Create a new SystemManager.
             * @param entityRegistry The EntityRegistry where the systems will execute.
             * @param resourceRegistry The ResourceRegistry where the systems will execute.
             * @param eventManager The EventManager where the systems will execute.
             */
            SystemManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, EventManager& eventManager) noexcept;

            /**
             * @brief Add a system to a schedule.
             * @tparam SystemType The system type.
             * @param schedule The schedule to add the system to.
             */
            template <typename SystemType>
            void addSystem(DefaultSchedules schedule) noexcept {
                static_assert(std::is_base_of<SystemInterface, SystemType>::value, "System must be a subclass of SystemInterface.");
                systems[schedule]->addSystem<SystemType>();
            }
            /**
             * @brief Add a system to a schedule.
             * @tparam Params... The lambda function parameters.
             * @tparam Func The lambda function type.
             * @param schedule The schedule to add the system to.
             * @param func The lambda function.
             * @see SystemParameter
             * @see Query, ReadRequest, WriteRequest, Commands
             */
            template <typename... Params, typename Func>
            void addSystem(DefaultSchedules schedule, Func func) noexcept {
                static_assert(std::is_invocable_r<void, Func, Params...>::value, "Func must be invocable with Params");
                systems[schedule]->addSystem<Params...>(func);
            }

            /**
             * @brief Run the startup schedule.
             */
            void startup() noexcept;
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
            std::unordered_map<DefaultSchedules, std::unique_ptr<SystemRegistry>> systems;  ///< The systems in the manager.
        };
    }  // namespace core::ecs
}  // namespace cobalt