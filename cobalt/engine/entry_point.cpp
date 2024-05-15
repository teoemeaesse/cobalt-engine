// Created by tomas on
// 03-12-2023

#include "engine/entry_point.h"

#include "core/ecs/exception.h"
#include "core/exception.h"
#include "engine/input/exception.h"
#include "engine/material/shader_library.h"

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
    }  // namespace engine
}  // namespace cobalt

int main(int argc, char** argv) {
    // Initialize the engine.
    cobalt::core::Log::init();
    cobalt::core::Platform::checkCompatibility();
    cobalt::core::Platform::log();
    cobalt::core::gl::Context::init();
    cobalt::engine::ShaderLibrary::init();

    // Create the application.
    auto app = cobalt::engine::createApplication();

    // Handle interrupts.
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = cobalt::engine::handleCtrlC;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    // Run the application.
    try {
        app->init();
        app->run();
    } catch (const cobalt::core::CoreExceptionInterface& e) {
        CB_CORE_ERROR(e.what());
    } catch (const std::exception& e) {
        CB_ERROR(e.what());
    }

    // Cleanup.
    delete app;
    cobalt::core::gl::Context::finish();

    return EXIT_SUCCESS;
}