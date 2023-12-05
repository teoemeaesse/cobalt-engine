//
// Created by tomas on 03-12-2023.
//

#include <signal.h>

#include "engine/entry_point.h"


namespace cobalt {
    namespace engine {
        bool shutdownInterrupt = false;

        void handleCtrlC(int s) {
            CB_WARN("Caught signal {0}", s);
            if (s == SIGINT) {
                CB_WARN("Shutting down");
                cobalt::engine::shutdownInterrupt = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    // Initialize the engine.
    cobalt::core::Log::init();
    cobalt::core::RenderContext::init();

    // Create the application.
    auto app = cobalt::engine::createApplication();
    cobalt::core::RenderContext::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
        cobalt::core::InputManager* inputManager = static_cast<cobalt::core::InputManager*>(cobalt::core::RenderContext::getUserPointer());
        CB_CORE_TRACE("Key: {0}, scancode: {1}, action: {2}, mods: {3}", key, scancode, action, mods);
        inputManager->getKeyboard().onKeyPress(key, action);
    });
    
    // Handle interrupts.
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = cobalt::engine::handleCtrlC;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    // Run the application.
    app->run();
    delete app;

    // Cleanup.
    cobalt::core::RenderContext::destroy();

    return EXIT_SUCCESS;
}