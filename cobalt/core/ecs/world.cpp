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

        void World::kill(const Entity& entity) noexcept {
            componentRegistry.removeAll(entity.getID());
            entityRegistry.remove(entity);
        }

        void World::update() noexcept {
            for (auto& schedule : schedules) {
                schedule.second->run();
            }
        }
    }  // namespace core::ecs
}  // namespace cobalt