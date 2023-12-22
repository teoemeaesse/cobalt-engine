//
// Created by tomas on 29-11-2023.
//

#include <time.h>

#include "engine/application.h"
#include "core/utils/log.h"
#include "core/gfx/render_context.h"


namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate) :
            targetFramerate(framerate),
            estimatedFramerate(0),
            shouldStop(false),
            frameCount(0),
            framerateTimeWindow(1),
            inputManager(1.0f),
            window(core::WindowBuilder()
                .setTitle("Cobalt")
                .setWidth(1280)
                .setHeight(720)
                .setVsync(true)
                .setCallbackSetter([]() {
                    core::RenderContext::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        inputManager.getKeyboard().onKeyPress(key, action);
                    });
                    core::RenderContext::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        inputManager.getMouse().onMove((float) xpos, (float) ypos);
                    });
                    core::RenderContext::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        inputManager.getMouse().onButtonPress(button, action);
                    });
                    core::RenderContext::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        inputManager.getMouse().onScroll((float) xoffset, (float) yoffset);
                    });
                    core::RenderContext::setResizeCallback([](GLFWwindow* window, int width, int height) {
                        Application* app = static_cast<Application*>(core::RenderContext::getUserPointer());
                        app->getWindow().onResize((float) width, (float) height);
                        app->onResize((float) width, (float) height);
                    });
                })
                .build()
            ) {
            core::RenderContext::setUserPointer(this);
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

        core::Window& Application::getWindow() {
            return window;
        }

        core::InputManager& Application::getInputManager() {
            return inputManager;
        }

        void Application::setFramerateTimeWindow(const uint timeWindow) {
            framerateTimeWindow = timeWindow;
        }

        void Application::onResize(const float width, const float height) {
            CB_CORE_INFO("Application's window resized to {0}x{1} px", width, height);
        }
    }
}