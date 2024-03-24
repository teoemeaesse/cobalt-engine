// Created by tomas on
// 08-02-2024

#pragma once

namespace cobalt {
    namespace core::ecs {
        class World;

        /**
         * @brief: Collection of systems, components and resources that can be easily added to / removed from an ECS world for self-contained
         * functionality.
         */
        class Plugin {
            public:
            /**
             * @brief: Construct a plugin.
             * @param title: Title of the plugin.
             * @param description: Description of the plugin.
             * @return: Plugin
             */
            Plugin(const std::string& title, const std::string& description) noexcept;

            /**
             * @brief: Destruct a plugin.
             * @return: void
             */
            virtual ~Plugin() = default;

            /**
             * @brief: Add systems, components and resources to the world.
             * @param world: World to add the plugin to.
             * @return: void
             */
            virtual void onPlug(World& world) const noexcept = 0;

            /**
             * @brief: Small log message to show that the plugin has been added to the world.
             * @return: void
             */
            void log() const noexcept;

            /**
             * @brief: Get the title for this plugin.
             * @return: std::string
             */
            const std::string& getTitle() const noexcept;

            private:
            std::string title;
            std::string description;
        };
    }  // namespace core::ecs
}  // namespace cobalt