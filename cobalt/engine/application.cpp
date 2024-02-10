// Created by tomas on
// 29-11-2023

#include "engine/application.h"

#include "core/gl/context.h"
#include "core/pch.h"
#include "engine/ecs/plugin/input.h"
#include "engine/ecs/plugin/time.h"

namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate)
            : targetFramerate(framerate),
              estimatedFramerate(0),
              shouldStop(false),
              frameCount(0),
              framerateTimeWindow(1),
              window(
                  core::gfx::WindowBuilder()
                      .setTitle("Cobalt")
                      .setWidth(1280)
                      .setHeight(720)
                      .setVsync(true)
                      .setCallbackSetter([]() {
                          core::gl::Context::setKeyCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
                              core::input::InputManager& inputManager =
                                  static_cast<Application*>(core::gl::Context::getUserPointer())->getInputManager();
                              try {
                                  inputManager.getPeripheral<core::input::Keyboard>(core::input::Keyboard::NAME).onKeyPress(key, action);
                              } catch (core::input::InvalidInputException<core::input::KeyboardInputID>& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              } catch (core::input::PeripheralNotFoundException& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              }
                          });
                          core::gl::Context::setCursorPosCallback([](GLFWwindow* window, double xpos, double ypos) {
                              core::input::InputManager& inputManager =
                                  static_cast<Application*>(core::gl::Context::getUserPointer())->getInputManager();
                              try {
                                  inputManager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onMove((float)xpos, (float)ypos);
                              } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              } catch (core::input::PeripheralNotFoundException& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              }
                          });
                          core::gl::Context::setMouseButtonCallback([](GLFWwindow* window, int button, int action, int mods) {
                              core::input::InputManager& inputManager =
                                  static_cast<Application*>(core::gl::Context::getUserPointer())->getInputManager();
                              try {
                                  inputManager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onButtonPress(button, action);
                              } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              } catch (core::input::PeripheralNotFoundException& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              }
                          });
                          core::gl::Context::setScrollCallback([](GLFWwindow* window, double xoffset, double yoffset) {
                              core::input::InputManager& inputManager =
                                  static_cast<Application*>(core::gl::Context::getUserPointer())->getInputManager();
                              try {
                                  inputManager.getPeripheral<core::input::Mouse>(core::input::Mouse::NAME).onScroll((float)xoffset, (float)yoffset);
                              } catch (core::input::InvalidInputException<core::input::MouseInputID>& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              } catch (core::input::PeripheralNotFoundException& e) {
                                  CB_CORE_ERROR("{}", e.what());
                              }
                          });
                          core::gl::Context::setFramebufferResizeCallback([](GLFWwindow* window, int width, int height) {
                              Application* app = static_cast<Application*>(core::gl::Context::getUserPointer());
                              app->getWindow().onResize((uint)width, (uint)height);
                              app->onResize((uint)width, (uint)height);
                          });
                          core::gl::Context::setResizeCallback([](GLFWwindow* window, int width, int height) {
                              Application* app = static_cast<Application*>(core::gl::Context::getUserPointer());
                              app->getWindow().setDimensions((uint)width, (uint)height);
                          });
                      })
                      .build()) {
            core::gl::Context::setUserPointer(this);
            world.addPlugin<InputPlugin>();
            world.addPlugin<TimePlugin>();
            CB_INFO("Created application");
            CB_INFO("Starting up ECS world");
            world.startup();
        }

        Application::~Application() { CB_INFO("Destroyed application"); }

        extern bool shutdownInterrupt;
        void Application::run() {
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(core::gl::Context::getGLFWContext(), &framebufferWidth, &framebufferHeight);
            onResize((uint)framebufferWidth, (uint)framebufferHeight);
            CB_INFO("Starting up game loop");

            uint64_t delta = 1000000 / targetFramerate, acc = 0, frametime = 0, counter = 0;
            uint frames = 0;
            struct timespec start, end;
            while (!shouldStop && !shutdownInterrupt) {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);

                while (acc >= delta) {
                    world.update();
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
                float delta = (float)frametime / 1000000.0f;
                Time& time = world.getResource<Time>();
                time.deltaTime = delta;
                time.elapsedTime += delta;

                if (getWindow().shouldClose()) {
                    stop();
                }
                window.clear();
                world.render();
                variableTimeStep(delta);
                window.swapBuffers();

                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                frametime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
                acc += frametime;
            }

            CB_INFO("Shutting down ECS world");
            world.shutdown();
            CB_INFO("Shutting down game loop");
        }

        void Application::stop() { shouldStop = true; }

        uint Application::getFramerate() const { return frameCount / framerateTimeWindow; }

        core::gfx::Window& Application::getWindow() { return window; }

        core::input::InputManager& Application::getInputManager() { return world.getResource<InputManager>().core; }

        void Application::setFramerateTimeWindow(const uint timeWindow) { framerateTimeWindow = timeWindow; }

        void Application::onResize(const uint width, const uint height) { CB_CORE_INFO("Application's window resized to {0}x{1} px", width, height); }
    }  // namespace engine
}  // namespace cobalt