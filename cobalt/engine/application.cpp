//
// Created by tomas on 29-11-2023.
//

#include <time.h>

#include "core/utils/log.h"
#include "core/gfx/render_context.h"
#include "engine/application.h"


namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate) :
            targetFramerate(framerate),
            estimatedFramerate(0),
            shouldStop(false),
            frameCount(0),
            framerateTimeWindow(1),
            inputManager(1.0f) {
            
            core::RenderContext::setUserPointer(&inputManager);
            // core::RenderContext::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
            //     core::InputManager* inputManager = static_cast<core::InputManager*>(core::RenderContext::getUserPointer());
            //     CB_CORE_TRACE("Key: {0}, scancode: {1}, action: {2}, mods: {3}", key, scancode, action, mods);
            //     inputManager->getKeyboard().onKeyPress(key, action);
            // });
            // core::RenderContext::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
            //     core::InputManager* inputManager = static_cast<core::InputManager*>(core::RenderContext::getUserPointer());
            //     inputManager->getMouse().onMove((float) xpos, (float) ypos);
            // });
            // core::RenderContext::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
            //     core::InputManager* inputManager = static_cast<core::InputManager*>(core::RenderContext::getUserPointer());
            //     inputManager->getMouse().onButtonPress(button, action);
            // });
            // core::RenderContext::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
            //     core::InputManager* inputManager = static_cast<core::InputManager*>(core::RenderContext::getUserPointer());
            //     inputManager->getMouse().onScroll((float) xoffset, (float) yoffset);
            // });
            // core::RenderContext::setErrorCallback([](int error, const char* description) {
            //     CB_CORE_ERROR("GLFW error {0}: {1}", error, description);
            // });
            

            CB_INFO("Created application");
        }

        Application::~Application() {
            CB_INFO("Destroyed application");
        }

        extern bool shutdownInterrupt;
        void Application::run() {
            CB_INFO("Starting up game loop");
            
            uint64_t delta = 1000000 / targetFramerate,
                        acc = 0, frametime = 0, counter = 0;
            uint frames = 0;
            struct timespec start, end;
            while(!shouldStop && !shutdownInterrupt) {
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

        core::InputManager& Application::getInputManager() {
            return inputManager;
        }
    }
}