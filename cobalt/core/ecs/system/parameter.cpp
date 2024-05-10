/**
 * @file parameter.h
 * @brief A system parameter is any object that can be passed to a System's argument list.
 * @author Tomás Marques
 * @date 13-02-2024
 */

#include "core/ecs/system/parameter.h"

namespace cobalt {
    namespace core::ecs {
        SystemParameter::SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                                         EventManager& eventManager) noexcept
            : entityRegistry(entityRegistry), resourceRegistry(resourceRegistry), systemManager(systemManager), eventManager(eventManager) {}
    }  // namespace core::ecs
}  // namespace cobalt