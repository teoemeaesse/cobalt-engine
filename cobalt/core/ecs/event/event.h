// Created by tomas on
// 14-02-2024

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
             * @brief Construct a new Event object
             * @param name The name of the event
             * @param description The description of the event
             * @return A new Event object
             */
            Event(const std::string& name, const std::string& description) noexcept;
            /**
             * @brief Destroy the Event object
             */
            virtual ~Event() = default;

            /**
             * @brief Check if two events are equal
             * @param other The other event
             * @return true if the events are equal, false otherwise
             */
            bool operator==(const Event& other) const noexcept;

            /**
             * @brief Log the event
             */
            void log() const noexcept;

            /**
             * @brief Get the name of the event
             * @return The name of the event
             */
            const std::string& getName() const noexcept;

            private:
            std::string name;
            std::string description;
        };
    }  // namespace core::ecs
}  // namespace cobalt