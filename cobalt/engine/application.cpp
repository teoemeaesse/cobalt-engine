// Created by tomas on
// 29-11-2023

#include "engine/application.h"

#include "core/gl/context.h"
#include "engine/bundle/base.h"

namespace cobalt {
    namespace engine {
        Application::Application(const uint framerate)
            : targetFramerate(framerate), estimatedFramerate(0), shouldStop(false), frameCount(0), framerateTimeWindow(1) {
            core::gl::Context::setUserPointer(static_cast<void*>(&world));
        }

        Application::~Application() { CB_INFO("Destroyed application"); }

        void Application::init() {
            CB_INFO("Adding plugins");
            addPlugins();
            CB_INFO("Starting up ECS world");
            world.startup();
            setup();
        }

        extern bool shutdownInterrupt;
        void Application::run() {
            int framebufferWidth, framebufferHeight;
            glfwGetFramebufferSize(core::gl::Context::getGLContext(), &framebufferWidth, &framebufferHeight);
            CB_INFO("Starting up game loop");

            uint64_t delta = 1000000 / targetFramerate, acc = 0, frametime = 0, counter = 0;
            uint frames = 0;
            struct timespec start, end;
            while (!shouldStop && !shutdownInterrupt) {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);

                while (acc >= delta) {
                    world.update();
                    glfwPollEvents();
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

                Window& window = getWindow();
                if (window.shouldClose()) {
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

        void Application::setFramerateTimeWindow(const uint timeWindow) { framerateTimeWindow = timeWindow; }

        Window& Application::getWindow() {
            try {
                if (!world.isPlugin("Window")) {
                    CB_ERROR("Window plugin not found, but requested.");
                }
                return world.getResource<Window>();
            } catch (const core::ecs::ResourceNotFoundException<Window>& e) {
                throw core::ecs::PluginNotFoundException("Window");
            }
        }

        const Window& Application::getWindow() const {
            try {
                if (!world.isPlugin("Window")) {
                    CB_ERROR("Window plugin not found, but requested.");
                }
                return world.getResource<Window>();
            } catch (const core::ecs::ResourceNotFoundException<Window>& e) {
                throw core::ecs::PluginNotFoundException("Window");
            }
        }

        InputManager& Application::getInputManager() {
            try {
                if (!world.isPlugin("Input")) {
                    CB_ERROR("Input plugin not found, but requested.");
                }
                return world.getResource<InputManager>();
            } catch (const core::ecs::ResourceNotFoundException<InputManager>& e) {
                throw core::ecs::PluginNotFoundException("Input");
            }
        }

        const InputManager& Application::getInputManager() const {
            try {
                if (!world.isPlugin("Input")) {
                    CB_ERROR("Input plugin not found, but requested.");
                }
                return world.getResource<InputManager>();
            } catch (const core::ecs::ResourceNotFoundException<InputManager>& e) {
                throw core::ecs::PluginNotFoundException("Input");
            }
        }
    }  // namespace engine
}  // namespace cobalt