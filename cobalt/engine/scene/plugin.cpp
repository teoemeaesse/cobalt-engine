// Created by tomas on
// 10-04-2024

#include "engine/scene/plugin.h"

#include "engine/scene/graph.h"

namespace cobalt {
    using namespace core;

    namespace engine {
        ScenePlugin::ScenePlugin() noexcept : ecs::Plugin(TITLE, "Provides scene graph functionality.") {}

        void ScenePlugin::onPlug(ecs::World& world) const noexcept {
            world.registerComponent<SceneGraph>();

            world.addSystem<ecs::Query<SceneGraph&>, ecs::Query<const SceneID&>>(ecs::DefaultSchedules::PreUpdate, [](auto graphQuery, auto idQuery) {
                for (auto [sceneGraph] : query) {
                    for (auto [id] : idQuery) {
                    }
                }
            });
        }

        ecs::Entity& ScenePlugin::addGraph(ecs::World& world) noexcept {
            ecs::Entity& graph = world.spawn();
            graph.add<SceneGraph>();
            graph.add<SceneID>(SceneID::create());
            return graph;
        }
    }  // namespace engine
}  // namespace cobalt