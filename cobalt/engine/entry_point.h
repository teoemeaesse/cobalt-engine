//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/utils/log.h"
#include "engine/application.h"


namespace cobalt {
    namespace engine {
        extern Application* createApplication();
    }
}

int main(int argc, char** argv) {
    cobalt::core::Log::init();
    CB_CORE_WARN("Initialized Log!");
    int a = 5;
    CB_INFO("Hello! Var={0}", a);

    auto app = cobalt::engine::createApplication();
    app->run();
    delete app;

    return EXIT_SUCCESS;
}