/**
 * @file event.h
 * @brief Events in the ECS, used to communicate between systems.
 * @author Tomás Marques
 * @date 14-02-2024
 */

#pragma once

#include "core/pch.h"

namespace cobalt {
    namespace core::ecs {
        /**
         * @brief An event is a message that is sent to the event manager to be processed by a system.
         */
        class Event {
            public:
            /**
             * @brief Construct a new Event.
             * @param name The name of the Event.
             * @param description The description of the Event.
             */
            Event(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief Destroy the Event.
             */
            virtual ~Event() = default;

            /**
             * @brief Check if two events are equal.
             * @param other The other event.
             * @return True if the events are equal, false otherwise.
             */
            bool operator==(const Event& other) const noexcept;

            /**
             * @brief Log the event.
             */
            void log() const noexcept;

            /**
             * @brief Get the name of the event.
             * @return The name of the event.
             */
            const std::string& getName() const noexcept;

            /**
             * @brief Get the description of the event.
             * @return The description of the event.
             */
            const std::string& getDescription() const noexcept;

            private:
            std::string name;         ///< The name of the event.
            std::string description;  ///< The description of the event.
        };
    }  // namespace core::ecs
}  // namespace cobalt