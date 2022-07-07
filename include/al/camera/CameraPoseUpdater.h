#pragma once

#include "al/camera/CameraPoser.h"
#include <sead/basis/seadTypes.h>

namespace al {
class CameraPoseUpdater {
public:
    u8 gap[0xa0];
    CameraPoser** mCameraPosers;
};

};