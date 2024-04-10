// Created by tomas on
// 29-11-2023

#pragma once

#include "engine/window/window.h"

namespace cobalt {
    namespace engine {
        /**
         * @brief The base class for all applications. This class is meant to be extended by the user.  A game loop will be run by the engine that
         * calls the update functions of the application.
         */
        class Application {
            public:
            /**
             * @brief Create a new application.
             * @param framerate The target framerate of the application.
             * @param window The window to use for the application.
             * @return The application.
             */
            Application(const uint framerate = 60);
            /**
             * @brief Destroy the application.
             */
            virtual ~Application();

            /**
             * @brief Initialize the application. This function MUST be called before the application is run.
             */
            void init();

            /**
             * @brief Add every plugin dependency.
             */
            virtual void addPlugins() = 0;

            /**
             * @brief Fixed time step update. Use this for physics and other things that need to be updated at a fixed rate.
             */
            virtual void fixedTimeStep() = 0;
            /**
             * @brief Variable time step update. Use this for rendering and other things that need to be updated as often as possible.
             * @param delta The time since the last frame.
             */
            virtual void variableTimeStep(const float delta) = 0;

            /**
             * @brief Run the application. This function will not return until the application is stopped.
             */
            void run();
            /**
             * @brief Stop the game loop.
             */
            void stop();

            /**
             * @brief Get the estimated framerate of the application.
             * @return The estimated framerate of the application.
             */
            uint getFramerate() const;
            /**
             * @brief Set the time window in which the estimated framerate is calculated.
             * @param timeWindow The time window in which the framerate is calculated, in seconds.
             */
            void setFramerateTimeWindow(const uint timeWindow);
            /**
             * @brief Get the window of the application.
             * @return The window of the application.
             */
            Window& getWindow();
            /**
             * @brief Get the window of the application.
             * @return The window of the application.
             */
            const Window& getWindow() const;
            /**
             * @brief Get the input manager of the application.
             * @return The input manager of the application.
             */
            InputManager& getInputManager();
            /**
             * @brief Get the input manager of the application.
             * @return The input manager of the application.
             */
            const InputManager& getInputManager() const;

            private:
            bool shouldStop;           // Whether the game loop should stop.
            uint targetFramerate;      // The target framerate of the application.
            uint estimatedFramerate;   // The estimated framerate of the application. Based on the framerate time window.
            uint64_t frameCount;       // The number of frames that have been rendered in the framerate time window.
            uint framerateTimeWindow;  // The time window in which the framerate is calculated, in seconds.

            protected:
            core::ecs::World world;  // The ECS world.

            /**
             * @brief Set up the derived class. Runs after the parent class has been initialized.
             */
            virtual void setup() = 0;
        };

        /**
         * @brief Create a new application. This function should be implemented by the user.
         * @return A pointer to the application.
         */
        Application* createApplication();
    }  // namespace engine
}  // namespace cobalt