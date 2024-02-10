// Created by tomas on
// 18-01-2024

#include "core/ecs/world.h"

namespace cobalt {
    namespace core::ecs {
        World::World() noexcept : entityRegistry(), componentRegistry() {
            for (auto schedule : {DefaultSchedules::Startup, DefaultSchedules::PreUpdate, DefaultSchedules::Update, DefaultSchedules::PostUpdate,
                                  DefaultSchedules::PreRender, DefaultSchedules::Render, DefaultSchedules::PostRender, DefaultSchedules::Shutdown}) {
                schedules.emplace(schedule, Move(createScope<Schedule>(entityRegistry, resourceRegistry)));
            }
        }

        Entity& World::spawn() noexcept { return entityRegistry.add(componentRegistry); }

        void World::startup() noexcept { schedules[DefaultSchedules::Startup]->run(); }

        void World::update() noexcept {
            for (DefaultSchedules schedule : {DefaultSchedules::PreUpdate, DefaultSchedules::Update, DefaultSchedules::PostUpdate}) {
                schedules[schedule]->run();
            }
        }

        void World::render() noexcept {
            for (DefaultSchedules schedule : {DefaultSchedules::PreRender, DefaultSchedules::Render, DefaultSchedules::PostRender}) {
                schedules[schedule]->run();
            }
        }

        void World::shutdown() noexcept { schedules[DefaultSchedules::Shutdown]->run(); }
    }  // namespace core::ecs
}  // namespace cobalt