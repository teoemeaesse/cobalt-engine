/**
 * @file parameter.h
 * @brief A system parameter is any object that can be passed to a System's argument list.
 * @author Tomás Marques
 * @date 07-02-2024
 */

#pragma once

namespace cobalt {
    namespace core::ecs {
        class EntityRegistry;
        class ResourceRegistry;
        class SystemManager;
        class EventManager;

        /**
         * @brief A SystemParameter is passed to a System's constructor and allows the System to interact with the World.
         */
        class SystemParameter {
            public:
            /**
             * @brief Default destructor.
             */
            virtual ~SystemParameter() noexcept = default;

            protected:
            /**
             * @brief Create a new SystemParameter.
             * @param entityRegistry The EntityRegistry where the system will execute.
             * @param resourceRegistry The ResourceRegistry where the system will execute.
             * @param systemManager The SystemManager where the system will execute.
             * @param eventManager The EventManager where the system will execute.
             */
            SystemParameter(EntityRegistry& entityRegistry, ResourceRegistry& resourceRegistry, SystemManager& systemManager,
                            EventManager& eventManager) noexcept;

            EntityRegistry& entityRegistry;      ///< The EntityRegistry where the system will execute.
            ResourceRegistry& resourceRegistry;  ///< The ResourceRegistry where the system will execute.
            SystemManager& systemManager;        ///< The SystemManager where the system will execute.
            EventManager& eventManager;          ///< The EventManager where the system will execute.
        };
    }  // namespace core::ecs
}  // namespace cobalt