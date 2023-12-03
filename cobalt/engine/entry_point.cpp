//
// Created by tomas on 03-12-2023.
//

#include <signal.h>

#include "engine/entry_point.h"


namespace cobalt {
    namespace engine {
        bool shutdownInterrupt = false;

        void handleCtrlC(int s) {
            CB_WARN("Caught signal {0}.", s);
            if (s == SIGINT) {
                CB_WARN("Shutting down.");
                cobalt::engine::shutdownInterrupt = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    cobalt::core::Log::init();
    cobalt::core::RenderContext::init();

    auto app = cobalt::engine::createApplication();
    
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = cobalt::engine::handleCtrlC;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    app->run();
    delete app;

    cobalt::core::RenderContext::destroy();

    return EXIT_SUCCESS;
}