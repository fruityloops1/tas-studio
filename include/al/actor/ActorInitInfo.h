#pragma once

#include "al/actor/Placement.h"

namespace al {

class ActorInitInfo {
public:
    void* gap;
    const al::PlacementInfo& mPlacementInfo;
};

} // namespace al