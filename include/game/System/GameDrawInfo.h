#pragma once

//#include "agl/DrawContext.h"

namespace agl
{
    struct DrawContext;
} // namespace agl


namespace al
{
    class GameDrawInfo {
        public:
            class RenderBuffer *mFirstRenderBuffer; // 0x0
            class RenderBuffer* mSecondRenderBuffer; // 0x8
            bool unkBool; // 0x10
            agl::DrawContext *mDrawContext; // 0x18
    };
} // namespace al
