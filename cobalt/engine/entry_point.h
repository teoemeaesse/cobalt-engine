//
// Created by tomas on 29-11-2023.
//

#pragma once

#include "core/gfx/render_context.h"
#include "engine/application.h"
#include "engine/internal/shader_library.h"
#include "engine/internal/material_library.h"


namespace cobalt {
    namespace engine {
        extern Application* createApplication();

        void handleCtrlC(int s);
    }
}