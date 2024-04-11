// Created by tomas on
// 03-12-2023

#include "engine/entry_point.h"

#include "core/ecs/exception.h"
#include "core/gl/exception.h"
#include "engine/input/exception.h"

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
    cobalt::engine::TextureLibrary::init();
    cobalt::engine::ShaderLibrary::init();
    cobalt::engine::MaterialLibrary::init();

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
    } catch (const cobalt::core::gl::GLException& e) {
        CB_ERROR(e.what());
    } catch (const cobalt::core::ecs::PluginDependencyNotFoundException& e) {
        CB_ERROR(e.what());
        return EXIT_FAILURE;
    } catch (const cobalt::core::ecs::ECSException& e) {
        CB_ERROR(e.what());
    } catch (const std::exception& e) {
        CB_ERROR(e.what());
    }

    // Cleanup.
    delete app;
    cobalt::core::gl::Context::finish();

    return EXIT_SUCCESS;
}