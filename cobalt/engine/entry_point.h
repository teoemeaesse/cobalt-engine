//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/utils/log.h"
#include "core/gfx/render_context.h"
#include "engine/application.h"


namespace cobalt {
    namespace engine {
        extern Application* createApplication();
    }
}

int main(int argc, char** argv) {
    cobalt::core::Log::init();
    cobalt::core::RenderContext::init();

    auto app = cobalt::engine::createApplication();
    
    delete app;

    cobalt::core::RenderContext::destroy();

    return EXIT_SUCCESS;
}