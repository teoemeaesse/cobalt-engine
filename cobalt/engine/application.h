//
// Created
// by
// tomas
// on
// 29-11-2023.
//

#pragma once

#include "core/gfx/window.h"
#include "core/input/input_manager.h"
#include "core/pch.h"

namespace cobalt {
    namespace engine {
        /** @brief: The base class for all applications.
         * This class is meant to be extended by the user.
         * A game loop will be run by the engine that calls the virtual methods of this
         * class.
         */
        class Application {
            public:
            /** @brief: Create a new application.
             * @param framerate: The target framerate of the application.
             * @param window: The window to use for the application.
             * @return: The application.
             */
            Application(const uint framerate = 60);
            /** @brief: Destroy the application.
             */
            virtual ~Application();

            /** @brief: Fixed time step update. Called every frame.
             * Use this for physics and other things that need to be updated at a fixed
             * rate.
             */
            virtual void fixedTimeStep() = 0;
            /** @brief: Variable time step update. Called as often as possible.
             * Use this for rendering and other things that need to be updated as often as
             * possible.
             * @param delta: The time since the last frame.
             */
            virtual void variableTimeStep(const float delta) = 0;

            /** @brief: Resize callback.
             * @param width: The new width of the window.
             * @param height: The new height of the window.
             */
            virtual void onResize(const uint width, const uint height);

            /** @brief: Run the application.
             * This function will not return until the application is stopped.
             */
            void run();
            /** @brief: Stop the game loop.
             */
            void stop();

            /** @brief: Get the estimated framerate of the application.
             * @return: The estimated framerate of the application.
             */
            uint getFramerate() const;
            /** @brief: Get the window.
             * @return: The window.
             */
            core::gfx::Window& getWindow();
            /** @brief: Get the input manager.
             * @return: The input manager.
             */
            core::input::InputManager& getInputManager();
            /** @brief: Set the time window in which the estimated framerate is calculated.
             * @param timeWindow: The time window in which the framerate is calculated, in
             * seconds.
             */
            void setFramerateTimeWindow(const uint timeWindow);

            private:
            bool shouldStop;           // Whether the game loop should stop.
            uint targetFramerate;      // The target framerate of the application.
            uint estimatedFramerate;   // The estimated framerate of the application. Based
                                       // on the framerate time window.
            uint64_t frameCount;       // The number of frames that have been rendered in the
                                       // framerate time window.
            uint framerateTimeWindow;  // The time window in which the framerate is
                                       // calculated, in seconds.

            core::gfx::Window window;                // The window.
            core::input::InputManager inputManager;  // The input manager.
        };

        /** @brief: Create a new application.
         * This function should be implemented by the user.
         * @return: A pointer to the application.
         */
        Application* createApplication();
    }  // namespace engine
}  // namespace cobalt