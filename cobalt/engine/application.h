//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/utils/types.h"
#include "core/input/input_manager.h"
#include "engine/internal/shader_library.h"
#include "engine/internal/texture_library.h"


namespace cobalt {
    namespace engine {
        /* The base class for all applications.
         * This class is meant to be extended by the user.
         * A game loop will be run by the engine that calls the virtual methods of this class.
         */
        class Application {
            public:
            /* Create a new application.
             * @param framerate: The target framerate of the application.
             * @return: The application.
             */
            Application(const uint framerate = 60);
            /* Destroy the application.
             */
            virtual ~Application();

            /* Fixed time step update. Called every frame.
             * Use this for physics and other things that need to be updated at a fixed rate.
             */
            virtual void fixedTimeStep() = 0;
            /* Variable time step update. Called as often as possible.
             * Use this for rendering and other things that need to be updated as often as possible.
             * @param delta: The time since the last frame.
             */
            virtual void variableTimeStep(const float delta) = 0;
            
            /* Run the application.
             * This function will not return until the application is stopped.
             */
            void run();
            /* Stop the game loop.
             */
            void stop();

            /* Get the estimated framerate of the application.
             * @return: The estimated framerate of the application.
             */
            uint getFramerate() const;
            /* Get the input manager.
             * @return: The input manager.
             */
            core::InputManager& getInputManager();
            /* Get the shader library.
             * @return: The shader library.
             */
            ShaderLibrary& getShaderLibrary();
            /* Get the texture library.
             * @return: The texture library.
             */
            TextureLibrary& getTextureLibrary();
            /* Set the time window in which the estimated framerate is calculated.
             * @param timeWindow: The time window in which the framerate is calculated, in seconds.
             */
            void setFramerateTimeWindow(const uint timeWindow);

            private:
            bool shouldStop;                    // Whether the game loop should stop.
            uint targetFramerate;               // The target framerate of the application.
            uint estimatedFramerate;            // The estimated framerate of the application. Based on the framerate time window.
            uint64_t frameCount;                // The number of frames that have been rendered in the framerate time window.
            uint framerateTimeWindow;           // The time window in which the framerate is calculated, in seconds.
        
            core::InputManager inputManager;    // The input manager.
            ShaderLibrary shaderLibrary;        // The shader library.
            TextureLibrary textureLibrary;      // The texture library.
        };

        /* Create a new application.
         * This function should be implemented by the user.
         * @return: A pointer to the application.
         */
        Application *createApplication();
    }
}