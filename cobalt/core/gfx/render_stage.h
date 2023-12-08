//
// Created by tomas on 08-12-2023.
//

#pragma once

#include "core/gfx/mesh_renderer.h"
#include "core/gfx/render_target.h"
#include "core/containers/vector.h"


namespace cobalt {
    namespace core {
        /* A render stage is a collection of render targets that can be
         * combined and rendered to a single target using a single renderer.
         */
        class RenderStage {
            public:
            template<typename... Sources>
            RenderStage(MeshRenderer renderer, Sources&&... args) : sources(1),  { 
                for (auto& source : {args...}) {
                    sources.push(source);
                }
            }
            virtual ~RenderStage() = default;

            private:
            Vector<RenderTarget*> sources;
            RenderTarget* target;
        };
    }
}