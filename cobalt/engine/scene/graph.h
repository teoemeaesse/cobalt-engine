/**
 * @file graph.h
 * @brief A scene graph for managing entities in a scene.
 * @author Tomás Marques
 * @date 27-08-2024
 */

#pragma once

#include "core/ecs/component/component.h"
#include "core/geom/octree.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief A scene graph used to manage entities in a scene, storing them in an Octree.
         */
        class SceneGraph : public core::ecs::Component {
            public:
            /**
             * @brief Create a scene graph.
             */
            SceneGraph() noexcept;

            /**
             * @brief Destroy the scene graph.
             */
            ~SceneGraph() noexcept = default;

            private:
        };
    }  // namespace engine
}  // namespace cobalt