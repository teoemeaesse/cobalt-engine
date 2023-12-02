//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/types/types.h"


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
             */
            Application(uint framerate = 60);
            /* Destroy the application.
             */
            virtual ~Application();

            /* Fixed time step update. Called every frame.
             * Use this for physics and other things that need to be updated at a fixed rate.
             */
            virtual void fixedTimeStep();
            /* Variable time step update. Called as often as possible.
             * Use this for rendering and other things that need to be updated as often as possible.
             * @param delta: The time since the last frame.
             */
            virtual void variableTimeStep(float delta);

            private:
            uint framerate;
        };

        /* Create a new application.
         * This function should be implemented by the user.
         * @return: A pointer to the application.
         */
        Application *createApplication();
    }
}