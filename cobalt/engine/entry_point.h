// Created by tomas on
// 29-11-2023

#pragma once

#include "core/gl/context.h"
#include "engine/application.h"

namespace cobalt {
    namespace engine {
        extern Application* createApplication();

        void handleCtrlC(int s);
    }  // namespace engine
}  // namespace cobalt