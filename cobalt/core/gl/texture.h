//
// Created by tomas on 30-11-2023.
//

#pragma once

#include "core/types/types.h"
#include "core/gl/definitions.h"


namespace cobalt {
    namespace core {
        class Texture {
            public:
            Texture(uint width, uint height);
            Texture(std::string& path);
            ~Texture();

            void bindToUnit(GLuint unit);

            private:
            GLHandle texture;
            uint width, height;
            uchar *data;
        }
    }
}