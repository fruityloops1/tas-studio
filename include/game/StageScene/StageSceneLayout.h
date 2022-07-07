#pragma once

#include "al/PlayerHolder/PlayerHolder.h"
#include "al/camera/SubCameraRenderer.h"
#include "al/layout/LayoutInitInfo.h"
#include "game/Layouts/CoinCounter.h"
#include "game/Layouts/ShineCounter.h"
#include <types.h>

class StageSceneLayout {
public:
    spad(gap, 0x18);
    CoinCounter* coinCounter; // 0x18
    spad(gap2, 0x8);
    ShineCounter* shineCounter; // 0x20

    StageSceneLayout(const char*, const al::LayoutInitInfo&, const al::PlayerHolder*, const al::SubCameraRenderer*);
    ~StageSceneLayout();
};