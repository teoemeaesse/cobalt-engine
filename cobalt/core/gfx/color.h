//
// Created by tomas on 02-12-2023.
//

#pragma once

#include "core/containers/types.h"


namespace cobalt {
    namespace core {
        typedef glm::vec4 Color;
        #define COLOR(r, g, b, a) glm::vec4(r, g, b, a)

        #define COLOR_WHITE COLOR(1.0f, 1.0f, 1.0f, 1.0f)
        #define COLOR_BLACK COLOR(0.0f, 0.0f, 0.0f, 1.0f)
        #define COLOR_RED COLOR(1.0f, 0.0f, 0.0f, 1.0f)
        #define COLOR_GREEN COLOR(0.0f, 1.0f, 0.0f, 1.0f)
        #define COLOR_BLUE COLOR(0.0f, 0.0f, 1.0f, 1.0f)
        #define COLOR_YELLOW COLOR(1.0f, 1.0f, 0.0f, 1.0f)
        #define COLOR_MAGENTA COLOR(1.0f, 0.0f, 1.0f, 1.0f)
        #define COLOR_CYAN COLOR(0.0f, 1.0f, 1.0f, 1.0f)
        #define COLOR_TRANSPARENT COLOR(0.0f, 0.0f, 0.0f, 0.0f)
    }
}