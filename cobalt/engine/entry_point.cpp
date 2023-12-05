//
// Created by tomas on 03-12-2023.
//

#include <signal.h>

#include "engine/entry_point.h"
#include "core/exceptions/container_exception.h"
#include "core/exceptions/gfx_exception.h"
#include "core/exceptions/input_exception.h"


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
        inputManager->getKeyboard().onKeyPress(key, action);
    });
    cobalt::core::RenderContext::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
        cobalt::core::InputManager* inputManager = static_cast<cobalt::core::InputManager*>(cobalt::core::RenderContext::getUserPointer());
        inputManager->getMouse().onMove((float) xpos, (float) ypos);
    });
    cobalt::core::RenderContext::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
        cobalt::core::InputManager* inputManager = static_cast<cobalt::core::InputManager*>(cobalt::core::RenderContext::getUserPointer());
        inputManager->getMouse().onButtonPress(button, action);
    });
    cobalt::core::RenderContext::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
        cobalt::core::InputManager* inputManager = static_cast<cobalt::core::InputManager*>(cobalt::core::RenderContext::getUserPointer());
        inputManager->getMouse().onScroll((float) xoffset, (float) yoffset);
    });

    // Handle interrupts.
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = cobalt::engine::handleCtrlC;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    // Run the application.
    try {
        app->run();
    } catch (const cobalt::core::GLException& e) {
        CB_ERROR("GL exception: {0}", e.what());
    } catch (const cobalt::core::InputException& e) {
        CB_ERROR("Input exception: {0}", e.what());
    } catch (const cobalt::core::GFXException& e) {
        CB_ERROR("GFX exception: {0}", e.what());
    } catch (const cobalt::core::ContainerException& e) {
        CB_ERROR("Container exception: {0}", e.what());
    } catch (...) {
        CB_ERROR("Unknown exception");
    }

    // Cleanup.
    delete app;
    cobalt::core::RenderContext::destroy();

    return EXIT_SUCCESS;
}