//
// Created by tomas on 29-11-2023.
//

#include "engine/application.h"
#include "core/utils/log.h"


namespace cobalt {
    namespace engine {
        Application::Application(uint framerate) : framerate(framerate) {
            CB_INFO("Application created");
        }

        Application::~Application() {
            CB_INFO("Application destroyed");
        }

        void Application::fixedTimeStep() {

        }

        void Application::variableTimeStep(float delta) {

        }
    }
}