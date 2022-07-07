#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/PlayerHolder/PlayerHolder.h"
#include "al/scene/Scene.h"
#include "sead/math/seadVector.h"
#include "types.h"

namespace al {

    class PadRumbleKeeper;

    class PlayerHolder {
      public:
        PlayerHolder(int);
        al::LiveActor* getPlayer(int);
        int* getPlayerNum() const;
        int* getBufferSize() const;
        void registerPlayer(al::LiveActor*, al::PadRumbleKeeper*);
    };
} // namespace al