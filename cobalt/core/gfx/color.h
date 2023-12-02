//
// Created by tomas on 02-12-2023.
//

#pragma once

#include "core/types/types.h"


namespace cobalt {
    namespace core {
        typedef glm::vec4 Color;

        #define COLOR_WHITE Color(1.0f, 1.0f, 1.0f, 1.0f)
        #define COLOR_BLACK Color(0.0f, 0.0f, 0.0f, 1.0f)
        #define COLOR_RED Color(1.0f, 0.0f, 0.0f, 1.0f)
        #define COLOR_GREEN Color(0.0f, 1.0f, 0.0f, 1.0f)
        #define COLOR_BLUE Color(0.0f, 0.0f, 1.0f, 1.0f)
        #define COLOR_YELLOW Color(1.0f, 1.0f, 0.0f, 1.0f)
        #define COLOR_MAGENTA Color(1.0f, 0.0f, 1.0f, 1.0f)
        #define COLOR_CYAN Color(0.0f, 1.0f, 1.0f, 1.0f)
        #define COLOR_TRANSPARENT Color(0.0f, 0.0f, 0.0f, 0.0f)
    }
}