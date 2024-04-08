// Created by tomas on
// 13-02-2024

#include "core/ecs/system/manager.h"

namespace cobalt {
    namespace core::ecs {
        SystemManager::SystemManager(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, EventManager& eventManager) noexcept
            : systems() {
            for (auto schedule : {DefaultSchedules::Startup, DefaultSchedules::PreUpdate, DefaultSchedules::Update, DefaultSchedules::PostUpdate,
                                  DefaultSchedules::PreRender, DefaultSchedules::Render, DefaultSchedules::PostRender, DefaultSchedules::Shutdown}) {
                systems.emplace(schedule, Move(CreateScope<SystemRegistry>(entityRegistry, resourceRegistry, *this, eventManager)));
            }
        }

        void SystemManager::startup() noexcept { systems[DefaultSchedules::Startup]->run(); }

        void SystemManager::update() noexcept {
            for (DefaultSchedules schedule : {DefaultSchedules::PreUpdate, DefaultSchedules::Update, DefaultSchedules::PostUpdate}) {
                systems[schedule]->run();
            }
        }

        void SystemManager::render() noexcept {
            for (DefaultSchedules schedule : {DefaultSchedules::PreRender, DefaultSchedules::Render, DefaultSchedules::PostRender}) {
                systems[schedule]->run();
            }
        }

        void SystemManager::shutdown() noexcept { systems[DefaultSchedules::Shutdown]->run(); }
    }  // namespace core::ecs
}  // namespace cobalt