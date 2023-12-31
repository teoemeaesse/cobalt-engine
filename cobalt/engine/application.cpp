//
// Created by tomas on 29-11-2023.
//

#include "engine/application.h"
#include "core/gfx/render_context.h"
#include "core/pch.h"


namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate) :
            targetFramerate(framerate),
            estimatedFramerate(0),
            shouldStop(false),
            frameCount(0),
            framerateTimeWindow(1),
            inputManager(),
            window(core::WindowBuilder()
                .setTitle("Cobalt")
                .setWidth(1280)
                .setHeight(720)
                .setVsync(true)
                .setCallbackSetter([]() {
                    core::RenderContext::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        try {
                            inputManager.getPeripheral<core::Keyboard>(core::Keyboard::NAME).onKeyPress(key, action);
                        } catch (core::InvalidInputException<core::KeyboardInputID>& e) {
                            CB_CORE_ERROR("{}", e.what());
                        } catch (core::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR("{}", e.what());
                        }
                    });
                    core::RenderContext::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        try {
                            inputManager.getPeripheral<core::Mouse>(core::Mouse::NAME).onMove((float) xpos, (float) ypos);
                        } catch (core::InvalidInputException<core::MouseInputID>& e) {
                            CB_CORE_ERROR("{}", e.what());
                        } catch (core::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR("{}", e.what());
                        }
                    });
                    core::RenderContext::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        try {
                            inputManager.getPeripheral<core::Mouse>(core::Mouse::NAME).onButtonPress(button, action);
                        } catch (core::InvalidInputException<core::MouseInputID>& e) {
                            CB_CORE_ERROR("{}", e.what());
                        } catch (core::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR("{}", e.what());
                        }
                    });
                    core::RenderContext::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
                        core::InputManager& inputManager = static_cast<Application*>(core::RenderContext::getUserPointer())->getInputManager();
                        try {
                            inputManager.getPeripheral<core::Mouse>(core::Mouse::NAME).onScroll((float) xoffset, (float) yoffset);
                        } catch (core::InvalidInputException<core::MouseInputID>& e) {
                            CB_CORE_ERROR("{}", e.what());
                        } catch (core::PeripheralNotFoundException& e) {
                            CB_CORE_ERROR("{}", e.what());
                        }
                    });
                    core::RenderContext::setFramebufferResizeCallback([](GLFWwindow* window, int width, int height) {
                        Application* app = static_cast<Application*>(core::RenderContext::getUserPointer());
                        app->getWindow().onResize((uint) width, (uint) height);
                        app->onResize((uint) width, (uint) height);
                    });
                    core::RenderContext::setResizeCallback([](GLFWwindow* window, int width, int height) {
                        Application* app = static_cast<Application*>(core::RenderContext::getUserPointer());
                        app->getWindow().setDimensions((uint) width, (uint) height);
                    });
                })
                .build()
            ) {
            core::RenderContext::setUserPointer(this);
            inputManager.registerPeripheral<core::Keyboard>(core::Keyboard::NAME);
            inputManager.registerPeripheral<core::Mouse>(core::Mouse::NAME, 1.0f);
            CB_INFO("Created application");
        }

        Application::~Application() {
            CB_INFO("Destroyed application");
        }

        extern bool shutdownInterrupt;
        void Application::run() {
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(core::RenderContext::getGLFWContext(), &framebufferWidth, &framebufferHeight);
            onResize((uint) framebufferWidth, (uint) framebufferHeight);
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

        void Application::onResize(const uint width, const uint height) {
            CB_CORE_INFO("Application's window resized to {0}x{1} px", width, height);
        }
    }
}