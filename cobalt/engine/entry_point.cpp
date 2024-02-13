// Created by tomas on
// 03-12-2023

#include "engine/entry_point.h"

#include "core/gfx/exception.h"
#include "core/input/exception.h"

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
        app->run();
    } catch (const cobalt::core::gl::GLException& e) {
        CB_ERROR("GL exception: {0}", e.what());
    } catch (const cobalt::core::gfx::GFXException& e) {
        CB_ERROR("GFX exception: {0}", e.what());
    } catch (const std::exception& e) {
        CB_ERROR("Exception: {0}", e.what());
    }

    // Cleanup.
    delete app;
    cobalt::core::gl::Context::destroy();

    return EXIT_SUCCESS;
}