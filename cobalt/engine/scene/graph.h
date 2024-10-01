/**
 * @file graph.h
 * @brief A scene graph for managing entities in a scene.
 * @author Tomás Marques
 * @date 27-08-2024
 */

#pragma once

#include "core/core.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A unique ID for a scene graph. Attach this to an entity to add it to the corresponding scene graph.
         */
        class SceneID : core::ecs::Component {
            public:
            /**
             * @brief Creates a scene ID.
             * @return The scene's ID.
             */
            static SceneID create() noexcept {
                static uint id = 0;
                return SceneID{id++};
            }

            /**
             * @brief Compares two scene IDs.
             * @param other The other scene ID.
             * @return Whether the scene IDs are equal.
             */
            bool operator==(const SceneID& other) const noexcept { return id == other.id; }

            private:
            uint id;  ///< The unique ID of a scene graph. // TODO: UUIDs

            /**
             * @brief Creates a scene ID.
             * @param id The scene's ID.
             */
            SceneID(uint id) noexcept : id{id} {}
        };

        /**
         * @brief A scene graph used to manage entities in a scene.
         * @warning This component should always be attached to the same entity as a SceneID.
         */
        class SceneGraph : core::ecs::Component {
            public:
            /**
             * @brief Creates a scene graph.
             */
            SceneGraph() noexcept = default;
            /**
             * @brief Destroys the scene graph.
             */
            ~SceneGraph() noexcept = default;

            private:
            core::geom::BVH<core::ecs::Entity&> staticEntities;    ///< Static entities such as terrain, buildings, etc.
            core::geom::DBVH<core::ecs::Entity&> dynamicEntities;  ///< Dynamic entities such as characters, vehicles, etc.
        };
    }  // namespace engine
}  // namespace cobalt