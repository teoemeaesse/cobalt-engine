/**
 * @file registry.cpp
 * @brief Storage for every type of components in the ECS.
 * @author Tomás Marques
 * @date 28-01-2024
 */

#include "core/ecs/component/registry.h"

namespace cobalt {
    namespace core::ecs {
        void ComponentRegistry::removeAll(const EntityProperties::ID& entityID) noexcept {
            for (const auto& [type, storage] : store) {
                storage->remove(entityID);
            }
            signatures[entityID].reset();
        }
    }  // namespace core::ecs
}  // namespace cobalt