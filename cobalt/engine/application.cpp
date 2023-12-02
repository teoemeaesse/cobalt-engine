//
// Created by tomas on 29-11-2023.
//

#include <time.h>

#include "core/utils/log.h"
#include "engine/application.h"


namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate) : targetFramerate(framerate), estimatedFramerate(0), shouldStop(false), frameCount(0), framerateTimeWindow(1) {
            CB_INFO("Created application");
        }

        Application::~Application() {
            CB_INFO("Destroyed application");
        }

        void Application::run() {
            CB_INFO("Starting up game loop");
            
            uint64_t delta = 1000000 / targetFramerate,
                        acc = 0, frametime = 0, counter = 0;
            uint frames = 0;
            struct timespec start, end;
            while(!shouldStop) {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);

                while(acc >= delta) {
                    fixedTimeStep();
                    acc -= delta;
                }

                frames++;
                counter += frametime;
                if (counter >= 1000000 * framerateTimeWindow) {
                    frameCount = frames;
                    counter = 0;
                    frames = 0;
                }
                float delta = (float) frametime / 1000000.0f;

                variableTimeStep(delta);

                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                frametime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
                acc += frametime;
            }

            CB_INFO("Shutting down game loop");
        }

        void Application::stop() {
            shouldStop = true;
        }

        uint Application::getFramerate() const {
            return frameCount / framerateTimeWindow;
        }
    }
}